freeCompute
===================================
说好听叫自己动手实现数学语言,DSL style!~
其实就是一个计算器而已啊混蛋!

###主要任务:
-----------------------------------
1. 词法分析(Lexer)
2. 语法分析,两种实现思路:
	- 双栈,转中缀到后缀,再计算后缀表达式.
	- 建立文法,自顶向下方法
3. 扩展:
	- 支持变量
	- 支持函数调用
	- 支持绘制函数图形
	- 支持if,for,while等
	- 等等

###编译:
-----------------------------------
采用C99标准.      
    
    gcc -std=c99 *.c
