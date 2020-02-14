# Examples

## Reference Provider & Consumer

The ReferenceProvider and Consumer replace the previous ExampleProvider and ExampleConsumer (which can still be found under _old).  
The ReferenceProvider and Consumer implement a minimal set of States and TestCases to verify compatibility to other implementations.  
The implementation is based on the description in doc/Reference.docx.  

To start the ReferenceProvider execute the binary from your build/bin directory using the command ./ReferenceProvider_d.  
You can also enable SSL using the -tls Flag.

To start the ReferenceConsumer execute the binary from your build/bin directory using the command ./ReferenceConsumer_d.  
Again, you can use -tls to enable SSL. Once executed you will be presented with the option to select the discovered Reference Provider.  
Alternatively, you can use-epr <YourProviderEndpointReference> to discover a specific endpoint. Notice that YourProviderEndpointReference can also only present the last 
characters of your endpointReference for convenience.

### Generate own SSL certificates
The ReferenceProvider and ReferenceConsumer have matching SSL certificates if you wish to generate your own certificates refer to doc/ssl.txt

### Logging
By default the logging of the ReferenceConsumer and ReferenceProvider are turned off. If you wish to see more information change:  
* SDCLibrary::getInstance().startup(OSELib::LogLevel::None);  
* DebugOut::DEBUG_LEVEL = DebugOut::Silent; 

to your desired LogLevel