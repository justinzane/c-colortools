##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=c-colortools
ConfigurationName      :=Debug
WorkspacePath          := "/home/justin/src"
ProjectPath            := "/home/justin/src/c-colortools"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=05/31/15
CodeLitePath           :="/home/justin/.codelite"
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="c-colortools.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)/usr/include/ $(IncludeSwitch)/usr/lib/gcc/x86_64-unknown-linux-gnu/5.1.0/include/ $(IncludeSwitch)/usr/lib/clang/3.6.0/include/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)pcre 
ArLibs                 :=  "pcre" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/llvm-ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   := -std=c11 -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/jzpnm.c$(ObjectSuffix) $(IntermediateDirectory)/clrtools.c$(ObjectSuffix) $(IntermediateDirectory)/pixels.c$(ObjectSuffix) $(IntermediateDirectory)/colorspaces.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/justin/src/c-colortools/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/jzpnm.c$(ObjectSuffix): jzpnm.c $(IntermediateDirectory)/jzpnm.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/justin/src/c-colortools/jzpnm.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/jzpnm.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jzpnm.c$(DependSuffix): jzpnm.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/jzpnm.c$(ObjectSuffix) -MF$(IntermediateDirectory)/jzpnm.c$(DependSuffix) -MM "jzpnm.c"

$(IntermediateDirectory)/jzpnm.c$(PreprocessSuffix): jzpnm.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jzpnm.c$(PreprocessSuffix) "jzpnm.c"

$(IntermediateDirectory)/clrtools.c$(ObjectSuffix): clrtools.c $(IntermediateDirectory)/clrtools.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/justin/src/c-colortools/clrtools.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/clrtools.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/clrtools.c$(DependSuffix): clrtools.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/clrtools.c$(ObjectSuffix) -MF$(IntermediateDirectory)/clrtools.c$(DependSuffix) -MM "clrtools.c"

$(IntermediateDirectory)/clrtools.c$(PreprocessSuffix): clrtools.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/clrtools.c$(PreprocessSuffix) "clrtools.c"

$(IntermediateDirectory)/pixels.c$(ObjectSuffix): pixels.c $(IntermediateDirectory)/pixels.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/justin/src/c-colortools/pixels.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pixels.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pixels.c$(DependSuffix): pixels.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pixels.c$(ObjectSuffix) -MF$(IntermediateDirectory)/pixels.c$(DependSuffix) -MM "pixels.c"

$(IntermediateDirectory)/pixels.c$(PreprocessSuffix): pixels.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pixels.c$(PreprocessSuffix) "pixels.c"

$(IntermediateDirectory)/colorspaces.c$(ObjectSuffix): colorspaces.c $(IntermediateDirectory)/colorspaces.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/justin/src/c-colortools/colorspaces.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/colorspaces.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/colorspaces.c$(DependSuffix): colorspaces.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/colorspaces.c$(ObjectSuffix) -MF$(IntermediateDirectory)/colorspaces.c$(DependSuffix) -MM "colorspaces.c"

$(IntermediateDirectory)/colorspaces.c$(PreprocessSuffix): colorspaces.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/colorspaces.c$(PreprocessSuffix) "colorspaces.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


