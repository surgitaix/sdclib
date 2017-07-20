# defaultgenerator.py
# 
# created 20.76.17
# 
# autor: Sebastian Buerger @ SurgiTAIX AG
#
# These classes generate the default.h/cpp, files that contain default values for each types. 
# The resulting file is not compilable and needs further editing. Annotations from the schema are extracted and appended to the file.


class DefaultDeclarationBuilder(object):
    def __init__(self):
        self.__functionDeclarations = ''

        
    def addFunction(self,complexTypeName):
        self.__functionDeclarations = self.__functionDeclarations + 'static CDM::' + complexTypeName + ' * ' + complexTypeName * '();\n'
        
    def getContent(self):
        return self.__functionDeclarations 
    

class DefaultDefinitionBuilder(object):
    def __init__(self):
        self.__functionDefinition = ''
        self.__includes = ''
        self.__annotations = ''
        
    def addFunction(self, complexTypeName, abstractBool):
        if not abstractBool:
            self.__includes = self.__includes + '#include \"OSCLib/Data/OSCP/MDIB/'+ complexTypeName + '.h\"\n'
            self.__functionDefinition = self.__functionDefinition + 'CDM::' + complexTypeName + '  * Defaults::' + complexTypeName * '() {\n\treturn new CDM::' + complexTypeName + '();\n}\n\n'
        
    def addAnnotation(self, complexTypeName, propertyName, annotationContent):
        self.__annotations = self.__annotations + '// Type:' + complexTypeName + ', Property: ' + propertyName + ', Annotation: ' + annotationContent + '.\n'
        
    def getContent(self):
        return self.__includes + self.__functionDefinition + self.__annotations