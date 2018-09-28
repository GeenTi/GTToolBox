//
//  ZXDataUntills.m
//  GTToolBox
//
//  Created by WMYeah on 15/8/25.
//  Copyright (c) 2015年 GeenTi（http://www.geenti.com）. All rights reserved.
//


#import "GTDataUntills.h"
#import <objc/runtime.h>

@implementation GTDataUntills

+ (NSString *)handleObjectTOJsonstringWithObject:(id)object objectClass:(Class)objectClass
{
    if (!objectClass) {
        return @"";
    }
    
    if ([objectClass isSubclassOfClass:[NSString class]]) {
        return object;
    }
    
    
    NSData *jsonData;
    
    if ([objectClass isSubclassOfClass:[NSDictionary class]] || [[objectClass class] isSubclassOfClass:[NSArray class]]) {
        
        jsonData = [NSJSONSerialization dataWithJSONObject:object options:kNilOptions error:nil];
    }else{
        NSMutableDictionary *mudDic = [NSMutableDictionary dictionary];
        unsigned int count;
        objc_property_t *properties = class_copyPropertyList(objectClass, &count);
        for(int i = 0; i < count; i++)
        {
            objc_property_t property = properties[i];
            
            NSString *propertyName = [[NSString alloc] initWithCString:property_getName(property) encoding:NSUTF8StringEncoding];
            
            NSString *value = [object valueForKey:propertyName];
            
            NSString *tovalue = [[[[[value stringByReplacingOccurrencesOfString:@"\\" withString:@""] stringByReplacingOccurrencesOfString:@"\"[" withString:@"["] stringByReplacingOccurrencesOfString:@"]\"" withString:@"]"] stringByReplacingOccurrencesOfString:@"\"{" withString:@"{"] stringByReplacingOccurrencesOfString:@"}\"" withString:@"}"];

            [mudDic setObject:tovalue forKey:propertyName];
        }
        jsonData = [NSJSONSerialization dataWithJSONObject:mudDic options:kNilOptions error:nil];
    }

    
    NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];

    
    NSString *toJsonString = [[[[[jsonString stringByReplacingOccurrencesOfString:@"\\" withString:@""] stringByReplacingOccurrencesOfString:@"\"[" withString:@"["] stringByReplacingOccurrencesOfString:@"]\"" withString:@"]"] stringByReplacingOccurrencesOfString:@"\"{" withString:@"{"] stringByReplacingOccurrencesOfString:@"}\"" withString:@"}"];
    
    return toJsonString;
}

+ (id)handleJsonsDicToObjectWithJsonDic:(NSDictionary*)jsonDic objectClass:(Class)objectClass
{
    id customObjc =[[objectClass alloc] init];
    
    for (NSString *key in jsonDic.allKeys) {
        
        [customObjc setValue:jsonDic[key] forKey:key];
    }
    return customObjc;
}

+ (NSString *)getVlueWihtObject:(id)object objectClass:(Class)objectClass property:(NSString *)propertyName
{
    if ([objectClass isSubclassOfClass:[NSString class]]) {
        return object;
    }
    
    unsigned int count;
    objc_property_t *properties = class_copyPropertyList(objectClass, &count);
    for(int i = 0; i < count; i++)
    {
        objc_property_t property = properties[i];
        
        NSString *propName = [[NSString alloc] initWithCString:property_getName(property) encoding:NSUTF8StringEncoding];
        
        if ([propName isEqualToString:propertyName] && propertyName != nil) {
            NSString *value = [object valueForKey:propertyName];
            return value;
        }
    }
    return nil;
}

+ (void)getDefaultVlueFromPropertyNameWithObject:(id)object objcetClass:(Class)objectClass
{
    unsigned int count;
    objc_property_t *properties = class_copyPropertyList(objectClass, &count);
    for(int i = 0; i < count; i++)
    {
        objc_property_t property = properties[i];
        
        NSString *propName = [[NSString alloc] initWithCString:property_getName(property) encoding:NSUTF8StringEncoding];
        
        [object setValue:propName forKey:propName];
    }
}


+ (id)parserNormalDataWithJSONData:(NSData *)jsondata model:(Class)modelclass
{
    if (jsondata == nil || modelclass == nil) {
        return nil;
    }
    NSDictionary *dataDic = [NSJSONSerialization JSONObjectWithData:jsondata options:kNilOptions error:nil];
    
    id model = [GTDataUntills handleJsonsDicToObjectWithJsonDic:dataDic objectClass:modelclass];
    
    return model;
}
@end
