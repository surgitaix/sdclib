# defaultgenerator.py
# 
# created 20.76.17
# 
# autor: Sebastian Buerger @ SurgiTAIX AG
#
# These classes generate the default.h/cpp, files that contain default values for each types. 
# The resulting file is not compilable and needs further editing. 


class DefaultDeclarationBuilder(object):
    def __init__(self):
        self.__functionDeclarations = ''


    def addFunction(self,complexTypeName, abstractBool, requiredProperties_list):
        if not abstractBool:
            self.__functionDeclarations = self.__functionDeclarations + '\tstatic CDM::' + complexTypeName + ' * ' + complexTypeName + 'Init('
            if requiredProperties_list:
                for item in requiredProperties_list:
                    typeArgumentTupel = item.split()
                    self.__functionDeclarations = self.__functionDeclarations + " ".join(typeArgumentTupel[:-1]) + " " + typeArgumentTupel[-1].lower() + ", "
                self.__functionDeclarations = self.__functionDeclarations[:-2]
            self.__functionDeclarations = self.__functionDeclarations + ');\n'
        
    def getContent(self):
        return self.__functionDeclarations 
   

class DefaultDefinitionBuilder(object):
    def __init__(self):
        self.__functionDefinition = ''
        self.__includes = ''
        
    def addFunction(self, complexTypeName, abstractBool, requiredProperties_list):
        if not abstractBool:
            self.__includes = self.__includes + '#include \"OSCLib/Data/OSCP/MDIB/'+ complexTypeName + '.h\"\n'
            self.__functionDefinition = self.__functionDefinition + 'CDM::' + complexTypeName + '  * Defaults::' + complexTypeName + 'Init('
            if requiredProperties_list:
                for item in requiredProperties_list:
                    typeArgumentTupel = item.split()
                    self.__functionDefinition = self.__functionDefinition + " ".join(typeArgumentTupel[:-1]) + " " + typeArgumentTupel[-1].lower() + ", "
                self.__functionDefinition = self.__functionDefinition[:-2]
                
            self.__functionDefinition = self.__functionDefinition + ') {\n\treturn new CDM::' + complexTypeName + '('
            if requiredProperties_list:
                requiredPropertiesVar_list = []
                for tupel in requiredProperties_list:
                    requiredPropertiesVar_list.append(tupel.split()[-1].lower())
                self.__functionDefinition = self.__functionDefinition + ", ".join([str(item) for item in requiredPropertiesVar_list])
            self.__functionDefinition = self.__functionDefinition + ');\n}\n\n'
                
    def getContent(self):
        return self.__functionDefinition 
    
    def getIncludes(self):
        return self.__includes + '\n\n'