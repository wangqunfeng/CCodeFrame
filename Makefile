###################################################################################
#                 简易多模块程序自动编译/清除Makefile v2.0
#简介：    自动编译、清除功能，不需要每次编译输入gcc或者rm指令
#使用方法: 先配置Makefile中的配置项、目标名称等，然后在终端执行make即可
#
#使用说明：1. 本Makefile可以自动推倒源程序与头文件之间的依赖关系，并生成.depend文件
#          2. 当目标目录不存在时，本Makefile将调用$(MKDIR)命令创建出完整的目标目录树
#          3. 在执行make clean命令时，将删除$(SRC)目录下所有匹配模式*~的文件，望悉知
#
#          Author: wangqunfeng, Date: 2013/12/30
#修改历史：
#          2014-1-9：添加2个编译过程中间输出文件：预处理.i，编译.s
#          2015-2-27: v2.0 自动推倒头文件依赖关系，支持创建目标目录
#################################用户配置选项######################################
TARGET = dict
OBJS = cworddb.o cwordserver.o eworderror.o


CXX = g++
GDB = gdb
MKDIR = mkdir
VPATH += ./:./include


CXXFLAGS = -g -std=c++11


SRC = ./src
BIN = ./bin/Debug
####################################################################################


#删除路径后面的斜线,并转换为路径序列
VPATH := $(patsubst %/,%,$(subst :, ,$(VPATH)))
#设置包含文件搜索路径
CXXFLAGS += $(addprefix -I,$(VPATH))


####################################################################################


all:bin depend $(BIN)/$(TARGET)


$(BIN)/$(TARGET) : $(addprefix $(BIN)/,$(OBJS))
	$(CXX) $(addprefix $(BIN)/,$(OBJS)) $(CXXFLAGS) -o $(BIN)/$(TARGET)


$(addprefix $(BIN)/,$(OBJS)): $(BIN)/%.o : $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@


-include $(BIN)/.depend


depend: 
	$(CXX) $(CXXFLAGS) -MM ${OBJS:%.o=$(SRC)/%.cpp} > $(BIN)/.depend


bin:
	[ ! -d $(BIN) ] & $(MKDIR) -p $(BIN)


clean:
	rm -rf $(SRC)/*~ $(BIN)/$(TARGET) $(addprefix $(BIN)/,$(OBJS)) $(BIN)/.depend


exec:
	$(BIN)/$(TARGET)


gdb:
	$(GDB) $(BIN)/$(TARGET)