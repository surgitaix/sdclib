# simpletypeshandling.py
# 
# created 06.07.17
# 
# autor: Sebastian Buerger @ SurgiTAIX AG
#
# this collection contains modules to build cpp classes for xsd:simpleTypes


# typedefs
class CppTypdefStringBuilder(object):
    
    def __init__(self, basetype_map):
        ## init basetype_map for converting xsd-basetypes to cpp-basetypes
        # if a type is unknown the compiler throws a KeyError!
        self.__basetype_map = basetype_map
        self.__itemListCounter = 0
        self.__basetypeCounter = 0
        self.__content = ''
    
    def addTypedef(self, simpleTypeName, baseTypeName_xsd):
        self.__content = self.__content + 'typedef ' + self.__basetype_map[baseTypeName_xsd] + ' ' + simpleTypeName + ';\n';
        self.__basetypeCounter = self.__basetypeCounter + 1
    
    # item list are always of basetype
    def addItemListTypedef(self, simpleTypeName, baseTypeName_xsd):
        self.__content = self.__content + 'typedef std::vector<' + self.__basetype_map[baseTypeName_xsd] + '> ' + simpleTypeName + ';\n';
        self.__itemListCounter = self.__itemListCounter + 1
    
    def getCppTypedefString(self):
        return self.__content + '\n\n'
    
    def getItemListCounter(self):
        return self.__itemListCounter
    
    def getBasetypeCounter(self):
        return self.__basetypeCounter
    
    
# enums
class CppEnumClassBuilder(object):
    
    def __init__(self, simpleTypeName):
        self.__content = 'enum class ' + simpleTypeName + '\n{\n'
        
    def appendEnumEntry(self, enum_name):
        self.__content = self.__content + '\t' + enum_name + ',\n'
        
    def getEnumClassAsString(self):
        return self.__content[:-2] + '\n};\n\n'
        

    
# EnumToStringClass declarations
# contains enum - counter
class CppEnumToStringClassDeclarationBuilder(object):
    
    def __init__(self):
        self.__content = 'class EnumToString {\npublic:\n\tEnumToString();\n\tvirtual ~EnumToString();\n'
        self.__enumCounter = 0
        
    def addConvertFunctionDeclarationForSimpleType(self, simpleTypeName):
        self.__content = self.__content + '\tstatic std::string convert(' + simpleTypeName + ' source);\n'
        self.__enumCounter = self.__enumCounter + 1
    
    def getEnumToStringClassDeclarationAsString(self):
        return self.__content + '};\n\n';

    def getEnumCounter(self):
        return self.__enumCounter
    
    
# EnumToStringClass definition
class CppEnumToStringClassDefinitionBuilder(object):
    
    def __init__(self,simpleTypeName):
        self.__simpleType_name = simpleTypeName
        self.__content = 'std::string EnumToString::convert(' + self.__simpleType_name + ' source) {\n\tswitch (source) {\n'
        
    def addConvertFunctionDefinitionForSimpleType(self,enum_name):
        self.__content = self.__content + '\t\tcase ' + self.__simpleType_name + '::' + enum_name + ': return \"' + enum_name + '\";\n';
        
    def getEnumToStringClassDefinitionsAsString(self):
        return self.__content + '\t}\n\tthrow std::runtime_error(\"Illegal value for ' + self.__simpleType_name + '\");\n}\n\n'

    
    