###################################################################################
#                 ���׶�ģ������Զ�����/���Makefile v2.0
#��飺    �Զ����롢������ܣ�����Ҫÿ�α�������gcc����rmָ��
#ʹ�÷���: ������Makefile�е������Ŀ�����Ƶȣ�Ȼ�����ն�ִ��make����
#
#ʹ��˵����1. ��Makefile�����Զ��Ƶ�Դ������ͷ�ļ�֮���������ϵ��������.depend�ļ�
#          2. ��Ŀ��Ŀ¼������ʱ����Makefile������$(MKDIR)�������������Ŀ��Ŀ¼��
#          3. ��ִ��make clean����ʱ����ɾ��$(SRC)Ŀ¼������ƥ��ģʽ*~���ļ�����Ϥ֪
#
#          Author: wangqunfeng, Date: 2013/12/30
#�޸���ʷ��
#          2014-1-9�����2����������м�����ļ���Ԥ����.i������.s
#          2015-2-27: v2.0 �Զ��Ƶ�ͷ�ļ�������ϵ��֧�ִ���Ŀ��Ŀ¼
#################################�û�����ѡ��######################################
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


#ɾ��·�������б��,��ת��Ϊ·������
VPATH := $(patsubst %/,%,$(subst :, ,$(VPATH)))
#���ð����ļ�����·��
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