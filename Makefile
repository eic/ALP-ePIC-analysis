SRC_DIR  := MyAnalysis
OBJ_DIR  := obj
LIB_DIR  := lib

CXX      := g++
EIC_INC  := -I/opt/local/include
EIC_LIBS := -L/opt/local/lib -ledm4eic -ledm4hep -lpodio -lpodioIO -lpodioRootIO

ROOT_CFLAGS := $(shell root-config --cflags)
ROOT_LIBS   := $(shell root-config --libs)
PY_INC      := $(shell python3-config --includes)

CLING_FLAGS := $(filter -I% -D%, $(ROOT_CFLAGS)) $(EIC_INC) -I$(SRC_DIR)
CXXFLAGS    := -fPIC -O3 -Wall -I. -I$(SRC_DIR) $(EIC_INC) $(ROOT_CFLAGS) $(PY_INC)
LDFLAGS     := -shared $(ROOT_LIBS) $(EIC_LIBS)

TARGET   := $(LIB_DIR)/libMyAnalysis.so
LINKDEF  := $(OBJ_DIR)/LinkDef.h
DICT     := $(OBJ_DIR)/MyDict.cxx
DICT_OBJ := $(OBJ_DIR)/MyDict.o
PCM      := $(OBJ_DIR)/MyDict_rdict.pcm

SRCS     := $(wildcard $(SRC_DIR)/*.cxx)
OBJS     := $(SRCS:$(SRC_DIR)/%.cxx=$(OBJ_DIR)/%.o) $(DICT_OBJ)
HEADERS  := $(wildcard $(SRC_DIR)/*.h)

DETECTED_CLASSES := $(shell grep -h "^[[:space:]]*class " $(HEADERS) 2>/dev/null | sed 's/^[[:space:]]*class //;s/[:{ ].*//' | sort | uniq)
GEN_PRAGMAS      := $(foreach cls,$(DETECTED_CLASSES),@echo "#pragma link C++ class $(cls)+;" >> $@;)


all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(ROOT_LIBS) $(EIC_LIBS)
	@cp $(PCM) $(LIB_DIR)/
	@echo "--- Build Complete: $(TARGET)"

$(LINKDEF): $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@echo "--- Auto-generating LinkDef.h in $(OBJ_DIR) ---"
	@echo "#ifdef __CLING__" > $@
	@echo "#pragma link C++ nestedclasses;" >> $@
	@echo "#pragma link C++ nestedtypedefs;" >> $@
	@for cls in $(DETECTED_CLASSES); do \
		echo "#pragma link C++ class $$cls+;" >> $@; \
		if [ "$$cls" != "MyAnalysis" ]; then \
			echo "#pragma link C++ class std::vector<$$cls>+;" >> $@; \
		fi \
	done
	@echo "#endif" >> $@

$(DICT): $(HEADERS) $(LINKDEF)
	@echo "--- Generating Dictionary for: $(DETECTED_CLASSES) ---"
	rootcling -f $@ -c -I. $(CLING_FLAGS) $(notdir $(HEADERS)) $(LINKDEF)

$(DICT_OBJ): $(DICT)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)

.PHONY: all clean
