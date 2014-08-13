all:testAlpha testBig testAll testGBK testJP
testAlpha:
	arm-linux-g++ neuHwrIface.cpp mytest.cpp -o testAlpha -DWINAPI= -DSTATIC_LINK -DENABLE_SEGMENTATION -DAI_ON -L./ -lPegatron_Alpha_pphwrV3_arm
testGBK:
	arm-linux-g++ neuHwrIface.cpp mytest.cpp -o testGBK -DWINAPI= -DSTATIC_LINK -DENABLE_SEGMENTATION -DAI_ON -L./ -lPegatron_GBK_pphwrV3_arm
testAll:
	arm-linux-g++ neuHwrIface.cpp mytest.cpp -o testAll -DWINAPI= -DSTATIC_LINK -DENABLE_SEGMENTATION -DAI_ON -L./ -lPegatron_Alpha_pphwrV3_arm -lPegatron_GBK_pphwrV3_arm -lPegatron_GBK_pphwrV3_arm -lPegatron_SJIS_pphwrV3_arm
testBig:
testJP:
