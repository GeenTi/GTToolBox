//
//  GTFuncExtension.h
//  GTToolBox
//
//  Created by WMYeah on 2017/11/14.
//  Copyright © 2017年 GeenTi. All rights reserved.
//

#ifndef GTFuncExtension_h
#define GTFuncExtension_h


//  常用 Block 定义；
typedef void(^GT_Block_Complate_Result)(id resultData);

typedef void(^GT_Block_Complate_Result_Data)(id resultData, NSError *error);

typedef void(^GT_Block_Complate)(void);

typedef void(^GT_Block_Complate_Result_dic)(NSDictionary *resultDic);

#endif /* GTFuncExtension_h */
