# gslmacrogenerator.py
# 
# created 06.76.17
# 
# autor: Sebastian Buerger @ SurgiTAIX AG
#
# this collection contains modules to build the macros for the GSL file generator (https://github.com/imatix/gsl)

# builds a macro for one class
class GSLClassBuilder(object):
    def __init__(self, class_name, parent_name, abstract_bool, customImpl_bool, apiInterfaces):
        # class_name: the name of the class / complex type
        # parent_name: the name of the class this class is derived from. 'NULL' if not derived
        # abstract_bool: true if class is abstract, false in the other case
        # apiInterfaces is a list of lists corresponding to a class. Each of these lists contains the classes' interfaces to the api. E.g. some 
        #     states needs to be accessed by the provider while others do not (e.g. context states do not)

        
        self.__apiInterfaces = apiInterfaces       
        self.__includedComplexTypes_list = list() # list for saving the complex types that are included already
        self.__includes = ''
        self.__properties = ''
        self.__propertylists = ''
        self.__typedefs = ''
        
        abstractConv = ['false', 'true']
        self.__abstract_string = abstractConv[abstract_bool]
        self.__classdeclaration = '\t<class name = \"' + class_name + '\" parent = \"' + parent_name + '\" abstract = \"' + self.__abstract_string + '\"'
        if customImpl_bool:
            self.__classdeclaration = self.__classdeclaration + ' customImpl = \"true\"'        
        self.__classdeclaration = self.__classdeclaration + '>\n'
        self.checkAndAddAPIInterface(class_name)
        
    def checkAndAddAPIInterface(self, class_name):
        for classInterfaceDescription in self.__apiInterfaces:
            if class_name == classInterfaceDescription[0]:
                for i in range(0,(len(classInterfaceDescription)-1)/2):
                    self.addTypedef(classInterfaceDescription[1+(2*i)], classInterfaceDescription[2+(2*i)])
        
    def addInclude(self,complexTypeName):
        # consider those types abstract that are named that way:
        if not (complexTypeName.find('Abstract') != -1):
            if not (complexTypeName in self.__includedComplexTypes_list):
                self.__includes = self.__includes + '\t\t<include path = \"OSCLib/Data/OSCP/MDIB/' + complexTypeName + '.h\" />\n'
                self.__includedComplexTypes_list.append(complexTypeName)
        
    def addProperty(self, property_name, property_type, optionality_string):
        self.__properties = self.__properties + '\t\t<property name = \"' + property_name + '\" type = \"' + property_type + '\" optional = \"' + optionality_string + '\" />\n'
    
    def addPropertyList(self, property_name, property_type):
        # automatically names nameServeral attaching a 's' to property_name
        self.__propertylists = self.__propertylists + '\t\t<propertyList nameSingle = \"' + property_name + '\" nameSeveral = \"' + property_name + 'Lists\" type = \"' + property_type + '\" />\n'
        
    def addTypedef(self, typedef_name, typedef_type):
        self.__typedefs = self.__typedefs + '\t\t<typedef name = \"' + typedef_name + '\" type = \"' + typedef_type + '\" />\n'

    def getGSLClassAsString(self):
        return self.__classdeclaration + self.__includes + self.__typedefs + self.__properties + self.__propertylists + '\t</class>\n\n'        
    
# contains the gsl descriptions
class GSLFileBuilder(object):
    def __init__(self):
        self.__numOfClasses = 0
        self.__content = '<?xml version="1.0"?>\n<classes script = \"generate.gsl\" >\n'

    def addClassAsString(self, class_string):
        self.__content = self.__content + class_string
        self.__numOfClasses = self.__numOfClasses + 1
        
    def getContent(self):
        return self.__content + '</classes>'
    
    def getNumOfClasses(self):
        return self.__numOfClasses
