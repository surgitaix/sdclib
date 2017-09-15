# xmlnodeparser.py
# 
# created 20.07.17
# 
# autor: Sebastian Buerger @ SurgiTAIX AG
#
# this collection contains modules to parse xml nodes for building C++ files and GSL macros

 
from gslmacrogenerator import GSLClassBuilder
 
# parses one complex type node
# build the gslFile, available via getGslClassBuilder
class ComplexTypeNodeParser(object):
    #static list of embedded nodes against double treatment
    __embeddedNodesNamesList = list()
    
    def __init__(self, simpleTypes_set, complexTypes_set, basetype_map, apiInterface, customImplList, simpleTypeNodeParser):
        # complexTypes_set: a set of all existing complexTypes. Complex types get own C++ Classes, thus they need to be references
        # simpleTypes_set: a set of all existing simpleTypes. simple types are all connected in simpleTypesMapping.cpp and are referenced to all complex classes by gsl script
        self.__simpleTypes_set = simpleTypes_set
        self.__complexTypes_set = complexTypes_set
        self.__basetype_map = basetype_map
        self.__apiInterface = apiInterface 
        self.__simpleTypeNodeParser = simpleTypeNodeParser
        self.__complexTypeName = ''
        self.__abstract_bool = False
        self.__parentTypeName = 'NULL'
        # classes are None from the beginning. Check before usage
        self.__gslClassBuilder = None
        self.__customImplList = customImplList
           
    def parseComplexTypeNode(self, cTNode_xpath):
        # only take nodes that have a 'name' attribute
        if 'name' in cTNode_xpath.attrib:
            # get name
            self.__complexTypeName = cTNode_xpath.attrib['name']
            ### structure analysis 
            hasParents = False
            # TODO : attribute == base check!!!
            for complexTypeParent_node in cTNode_xpath.xpath('./*/xsd:extension', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                hasParents = True
                for parentAttribute_name in complexTypeParent_node.attrib:
                    parentName_xsd = complexTypeParent_node.attrib[parentAttribute_name]
                    # get rid of the namespace prefix
                    self.__parentTypeName = parentName_xsd[(parentName_xsd.index(':')+1):]

            # consider only those types abstract that are named that way:
            self.__abstract_bool =  (self.__complexTypeName.find('Abstract') != -1)
             # gsl-file
            
            customImpl_bool = (self.__complexTypeName in self.__customImplList) 
            self.__gslClassBuilder = GSLClassBuilder(self.__complexTypeName, self.__parentTypeName, self.__abstract_bool, customImpl_bool, self.__apiInterface)      
            print 'debug: ' + self.__complexTypeName + ', parent= ' + self.__parentTypeName + ', abstract= ' + str(self.__abstract_bool)

            ## elements
            # elements have to be parsed before the attribute to provide a list of all embedded attributes
            elements_list = cTNode_xpath.xpath('./xsd:sequence/xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'})   + cTNode_xpath.xpath('./xsd:all/xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) + cTNode_xpath.xpath('./xsd:choice/xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) + cTNode_xpath.xpath('./xsd:complexContent/xsd:extension/xsd:sequence/xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'})
            for elementNode in elements_list:
                if 'name' in elementNode.attrib:
                    if not elementNode.attrib['name'] in ComplexTypeNodeParser.__embeddedNodesNamesList:
                        try:
                            element_name, element_type = self.__parseProperty(elementNode)
                            self.__parseElementsOccurenceAndOptionality(elementNode, element_name, element_type)
                        except ValueError as error:
                            print error.args[0]
                
            ## attributes
            attributeNodes = cTNode_xpath.xpath('./xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) + cTNode_xpath.xpath('./xsd:complexContent/xsd:extension/xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) + cTNode_xpath.xpath('./xsd:simpleContent/xsd:extension/xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) 
            for attribute_node in attributeNodes:
                # do not consider embedded attributes from this node
                if not attribute_node.attrib['name'] in ComplexTypeNodeParser.__embeddedNodesNamesList:
                    try:
                        attribute_name, attribute_type = self.__parseProperty(attribute_node)
                        self.__parseAttributesOptionality(attribute_node, attribute_name, attribute_type)
                    except ValueError as error:
                        print error.args[0]

                        
    
    def __parseProperty(self, xmlNode_xpath):
        # check if element is a valid node by checking if attr. name exists
        if 'name' in xmlNode_xpath.attrib:
            nodeName = xmlNode_xpath.attrib['name']
            
            if 'type' in xmlNode_xpath.attrib:
                # EXCLUDE abstract elements from being added
                # include those in the corresponding customImpls
                # the GSL implementaion can not handle abstract classes
                nodeType_xsd = xmlNode_xpath.attrib['type']
                if (nodeType_xsd.find('Abstract') == -1):
                
                    # get rid of the namespace prefix
                    nodeType = nodeType_xsd[(nodeType_xsd.index(':')+1):]
                    
                    # check if linked to a complexType -> include is necessary
                    if nodeType in self.__complexTypes_set:
                        self.__gslClassBuilder.addInclude(nodeType)
                    elif not (nodeType in self.__simpleTypes_set):
                        # check if datatype is a basetype -> transform in case of
                        # this is done after the checking for the complexTypes to assure that the compiler complains when a new unknown basetype occurs
                        nodeType = self.__basetype_map[nodeType_xsd]
                    
                    return nodeName, nodeType
                
                # throw warning if referencing an abstract type
                raise ValueError('Info linking an abstract type: Property ' + nodeName + '. Please ensure a proper implementation in the customImpl.') 
                
            # check for embedded types in elements with no 'type' attribute
            else:
                embeddedComplexTypeNode = xmlNode_xpath.xpath('./xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'})
                if embeddedComplexTypeNode:
                    # embedded complex classes do not have an own type name, thus named with a Type prefix
                    # add name attribute to embedded type node to convert it in the non-embedded form
                    # since the node is a mutable object this is done at the original node which is going to be parsed the next time.
                    # this approach is more efficient then utilizing recursion
                    embeddedComplexTypeNode[0].set('name', nodeName)
#                     embeddedComplexTypeNode[0].set('name', nodeName + 'Type')
                    ComplexTypeNodeParser.__embeddedNodesNamesList.append(nodeName)
                    # add include
                    self.__gslClassBuilder.addInclude(nodeName)
                    self.__complexTypes_set.add(nodeName)
                    print 'embedded complex type node created: ' +  nodeName
                    return nodeName, nodeName
#                     return nodeName, nodeName + 'Type'w
                    
                embeddedSimpleTypeNode = xmlNode_xpath.xpath('./xsd:simpleType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'})
                if embeddedSimpleTypeNode:
#                     embeddedSimpleTypeNode[0].set('name', nodeName + 'Type')
                    embeddedSimpleTypeNode[0].set('name', nodeName)
                    self.__simpleTypeNodeParser.parseSimpleTypeNode(embeddedSimpleTypeNode[0])
                    ComplexTypeNodeParser.__embeddedNodesNamesList.append(nodeName)
                    print 'embedded simple type node created: ' +  nodeName
                    return nodeName, nodeName
                
                # throw error if control gets here
                raise ValueError('WARNING: Property ' + nodeName + ' has no attribute type defined.') 
        else:
            raise ValueError('WARNING: Property has no attribute name defined.') 
    
    def __parseAttributesOptionality(self, attribute_node, attribute_name, attribute_type):
        optionality_string = 'true'
        if 'use' in attribute_node.attrib:
            if attribute_node.attrib['use'] == 'required':
                optionality_string = 'false'

        # add class
        self.__gslClassBuilder.addProperty(attribute_name, attribute_type, optionality_string)
        print '>> Attribute -> Property: ' + attribute_name + ', type= ' +  attribute_type + ', optional= ' + optionality_string
                
    def __parseElementsOccurenceAndOptionality(self, element_node, element_name, element_type):
        # depending on the occurence, the datatyp's fields for xsd:elements are defined
        # element + max occurence = unbounded -> propertyList
        if 'maxOccurs' in element_node.attrib:
            if element_node.attrib['maxOccurs'] == 'unbounded':
                self.__gslClassBuilder.addPropertyList(element_name, element_type)
                print '>> PropertyList: ' + element_name + ', type= ' + element_type
        
        else:
            # element + !maxoccurence + min occurence = 0 -> optional property
            if 'minOccurs' in element_node.attrib:
                if element_node.attrib['minOccurs'] == '0':
                    elementOptional = 'true'

            # element, without min/max occurence entry -> min=max=1 -> non-optional property
            else: 
                elementOptional = 'false'       
            # add class
            self.__gslClassBuilder.addProperty(element_name, element_type, elementOptional)
            print '>> Element -> Property: ' + element_name + ', type= ' + element_type + ', optional= ' + elementOptional 

    def getGSLClassBuilder(self):
        return self.__gslClassBuilder

    def getComplexTypeName(self):
        return self.__complexTypeName
    
    def getAbstractBool(self):
        return self.__abstract_bool

    def hasEmbeddedType(self):
        return self.__hasEmbeddedComplexType

    # debug. TODO delete
    def getEmbeddedAttributesNamesList(self):
        return self.__embeddedNodesNamesList
    
    
class SimpleTypeNodeParser(object):
    def __init__(self, classBuilderForwarder, simpleTypes_set):
        self.__classBuilderForwarder = classBuilderForwarder
        self.__simpleTypes_set = simpleTypes_set 
        
    def parseSimpleTypeNode(self, simpleTypeNode):
        # get the name of the simple type
        enumInit_flag = False
        isEnum = False
        if 'name' in simpleTypeNode.attrib:
            simpleTypeName = simpleTypeNode.attrib['name'] # attribute_name = 'name'
            self.__simpleTypes_set.add(simpleTypeName)
            print simpleTypeName
            
            # destinguish between enums and basetypes/itemlists
            # enums
            for enumNode in simpleTypeNode.xpath('./xsd:restriction/xsd:enumeration', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):    
                enumEntry = enumNode.attrib['value']
                print 'enum-type>>' + enumEntry
                # enum_Flag is False at the beginning of a new enum class -> reset classes
                if not enumInit_flag:
                    enumInit_flag = True
                    isEnum = True
                    self.__classBuilderForwarder.initEnumClassBuilders(simpleTypeName)

                self.__classBuilderForwarder.addEnumEntry(enumEntry)
            
            # append code for each enum class
            if isEnum:
                self.__classBuilderForwarder.finalizeEnumClass(simpleTypeName)
            
            # non enums
            if not isEnum:
                # basetypes
                for baseTypeNode in simpleTypeNode.xpath('./xsd:restriction', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'base' in baseTypeNode.attrib:
                        basetypeType = baseTypeNode.attrib['base']
                        print 'base-type>>' + basetypeType
                        self.__classBuilderForwarder.addBasetype(simpleTypeName,basetypeType)
                        
                # item lists
                for itemListNode in simpleTypeNode.xpath('./xsd:list', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'itemType' in itemListNode.attrib:
                        itemListName = itemListNode.attrib['itemType']
                        print 'itemList-type>>' + itemListName
                        self.__classBuilderForwarder.addItemlist(simpleTypeName, itemListName)
                        
                for unionTypeNode in simpleTypeNode.xpath('./xsd:union', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'memberTypes' in unionTypeNode.attrib:
                        # handle as basetype
                        basetypeType = unionTypeNode.attrib['memberTypes']
                        self.__classBuilderForwarder.addBasetype(simpleTypeName,basetypeType)
                        print 'union-type>>' + basetypeType

    