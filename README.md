# 2_MyFPS_UE4.27
 第一人称射击类游戏的demo
 由从源码编译的UE 4.27开发，实现人物移动、粒子发射、宝箱拾取、火药桶爆炸、血条显示等功能
•分离角色旋转和相机旋转，解决角色原地转圈问题
•实现粒子发射功能，对发射动作中手部骨骼位点和粒子发射位点进行同步
•将编写的函数需要绑定到“组件命中时”事件上，实现粒子对火药桶的碰撞和爆炸功能
•通过射线检测碰撞，利用GameplayInterface类的子类实现公共打开宝箱接口，降低模块之间耦合度

