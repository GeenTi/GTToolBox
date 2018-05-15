//
//  GTFuncExtension.h
//  GTToolBox
//
//  Created by WMYeah on 2017/11/14.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#ifndef GTFuncExtension_h
#define GTFuncExtension_h



/**
 GT BLock 带返回值

 @param resultData 返回值
 */
typedef void(^GT_Block_Complate_Result)(id resultData);

typedef void(^GT_Block_Complate_Result_Data)(id resultData, NSError *error);

typedef void(^GT_Block_Complate)(void);

typedef void(^GT_Block_Complate_Result_dic)(NSDictionary *resultDic);

#endif /* GTFuncExtension_h */
