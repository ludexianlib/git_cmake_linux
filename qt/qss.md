# QSS 语法

## 一、加载QSS
```c++
QFile qss("*.qss"); // qss文件名
qss.open(QFile::ReadOnly);
app.setStyleSheet(qss.readAll());
```
## 二、选择器
|   选择器  |    举例    |  解释    |
|   :----:  |   :----:  |   :----:  |
|   通用    |   *       |   所有widget  |
|   类型    |   QWidget |   QPushButton及其子类  |
|   类      |   .Widget |   作用于Widget但不匹配其子类   |
|   ID      |   #objName |   作用于对象名称为objName   |
|   后代    |   QWidget QPushButton |   QWidget子孙级的QPushButton   |
|   子级    |   QWidget > QPushButton |   QWidget直接子级的QPushButton  |
|   子控制  |   QComboBox::drop-down |   将规则限制到特定的widget子控件  |
## 三、伪状态（常用）
|   伪状态  |    说明    |
|   :----:  |   :----:  |
|   :active  |   widget驻留在活动窗口中时状态  |
|   :bottom  |   该项目位于底部  |
|   :checked  |   该项目已选中  |
|   :default  |   默认值  |
|   :enabled  |   该项已启用  |
|   :focus  |   具有输入焦点  |
|   :hover  |   鼠标悬停  |
|   :maximized  |   最大化  |
|   :pressed  |   鼠标按下  |
|   :read-only  |   只读或不可编辑  |
|   :off  |   适用于处于“关闭”状态的项目（还有on）  |
|   :left  |   项目位于左侧（还有right，top，bottom）  |
```css
/* 表格子控件示例 */
QTableWidget {
    ...
    alternate-background-color: /* 交错颜色 */
    gridline-color: 
}
QTableWidget::item:selected {
    ...
}
QTableWidget::item:hover {
    ...
}
    /* 表头 */
QHeaderView::section {

}
    /* 滑块 */
QScrollBar::handle:vertical {
    ...
}
    /* 滑块悬浮 */
QScrollBar::handle:hover:vertical {
    ...
}
    /* 滑块已，未划过区域 */
QScrollBar::sub-page:vertical, QScrollBar::add-page:vertical {
    ...
}
    /* 页面上下移按钮 */
QScrollBar::sub-line:vertical, QScrollBar::add-line:vertical {
    ...
}
```
## 四、样式语法规则
```css
width: 12px;		 /*设置宽度 单位像素*/
height: 40px  		 /*设置高度*/
min-width: 65px;     /*最小宽度*/
min-height:12px;     /*最小高度*/
max-width:12px;
max-height:12px;  
/*设置背景颜色  四种颜色表示方式*/
background-color: rgb(255,255,255);  
background-color: rgba(255,255,255,30);
background-color: yellow     			/*常用颜色名*/
background-color: #FF0000

colo: rgb(255,255,255);   				/*前景色 文本颜色*/
color: #F5F5F5;                         /*前景(文本)颜色*/
color: qlineargradient();               /*前景(文本)颜色:线性渐变*/
color: qradialgradient();               /*前景(文本)颜色:辐射渐变*/
color: qconicalgradient();              /*前景(文本)颜色:梯形渐变*/


font-size: 20px  						/*字体大小*/
font-family: Microsoft YaHei			/*字体选择  更多字体见附录*/

margin: 14px 18px 20px 18px;			/*外边距 顺序上右下左*/
margin-top: 14px;
margin-right: 18px;
margin-bottom: 20px;
margin-left: 18px;

padding: 4px;                            /* 内边距  顺序上右下左*/
padding-left: 5px;                       /* 文字左边距 */
padding-right: 10px;                     /* 文字右边距 */
padding-top: 3px;                        /* 文字顶边距 */
padding-bottom: 3px;                     /* 文字底边距 */
 
border: 3px solid red  					 /* 边框---可以分开设置 */
/*solid 实线 dotted 点状边框 dashed 虚线*/

border-width                             /* 边框厚度 */
border-top/right/bottom/left-width 

border: 1px solid #FDBC03;                   /* 边框:宽度 颜色*/  
border-image: url(boder.png) 4 8 12 16;      /* 边界图 切线 */  
border-radius: 4px;                          /* 边框圆角半径 */  
border-top-left-radius: ;                    /* 角弧度:左上角*/  
border-top-right-radius: ;                   /* 角弧度:右上角*/  
border-bottom-left-radius: ;                 /* 角弧度:左下角*/  
border-bottom-right-radius: ;                /* 角弧度:右下角*/  
double  双线
groove 定义3D凹槽边框
ridge 定义3D垄状边框
inset 定义3D inset边框
outset 定义3D outset边框

/* 边框颜色 上 右 下 左 */
border-color:
border-top/right/bottom/left-color

/*子部件列表*/                                
::down-arrow         /* combo box或spin box的下拉箭头 */
::down-button        /* spin box的向下按钮 */
::drop-down          /* combo box的下拉箭头 */
::indicator          /* checkbox、radio button或可选择group box的指示器 */
::item               /* menu、menu bar或status bar的子项目 */
::menu-indicator     /* push button的菜单指示器 */
::title              /* group box的标题 */
::up-arrow           /* spin box的向上箭头 */
::up-button          /* spin box的向上按钮 */
```
## 五、渐变示例
```css
/* 线性渐变起点(x1, y1)和终点(x2, y2)，以左上角为原点 */
background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 rgb(128, 128, 128), stop: 0.5 rgb(78, 78, 78), stop: 1 rgb(128, 128, 128));
/* 左上角为原点，圆心(cx, cy), 渐变半径（radius），渐变圆心（fx,fy) */
background: qradialgradient(cx: 0.5, cy: 0.5, radius: 1, fx: 0.5, fy: 0.5, stop: 0.3 rgb(78, 78, 78), stop: 1 rgb(128, 128, 128));
```
## 六、附录

1. 标准色
```
aqua, black, blue, fuchsia, gray, green, lime, maroon, navy,
olive, orange, purple, red, silver, teal, white, yellow
```
2. 中文字体对应名称
```
微软雅黑： Microsoft YaHei
宋体：SimSun
黑体：SimHei
仿宋： FangSong
楷体：  KaiTi
隶书：LiSu
幼圆：YouYuan
华文细黑：STXihei
华文楷体：STKaiti
华文宋体：STSong
华文中宋：STZhongsong
华文仿宋：STFangsong
方正舒体：FZShuTi
方正姚体：FZYaoti
华文彩云：STCaiyun
华文琥珀：STHupo
华文隶书：STLiti
华文行楷：STXingkai
华文新魏：STXinwei
```