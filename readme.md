目录说明
1、hellowworld是pjsua_simple的demo代码实验（仅hellowworld.cpp），还有从pjsua原项目贴过来的，用来参考的代码（没有引入项目，但是在文件夹里）
	重点参考对象为pjsua_app.c，第1289行static pj_status_t app_init()是它的初始化及各种绑定函数，里面还有很多回调、还有各种包括媒体绑定之类的东西，需要实验。
2、图形化工程项目为MFCApplication1
	是一个实现了包括sip呼叫、接听、挂断，通话过程中发送dtmf消息的图形化demo，附带来电音和呼叫回铃音。
	include/文件夹内为从pjproject-2.7出拷贝来的项目引用目录
	lib/文件夹是从pjproject-2.7拷贝来的编译好的pjsua项目的lib文件，作为项目的附加依赖项
	res/文件夹内是图形化应用用到的贴图



