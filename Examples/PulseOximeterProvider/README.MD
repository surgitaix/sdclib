The PulseOximeterProvider is a virtual device representation of the pulox PO-250.  
The device can be accessed via a serial connection between the pulse oximeter and the system running the provider application using the provided USB Cable.  
To use the serial connection the software library ASIO (https://think-async.com/Asio/) is integrated in the *Dependency* folder as git submodule. To download, execute ``git submodule update --init`` in the project root folder.    
To start the application ensure you are connected to the Device.  
Set the COMPort in the PulseOximeterProviderMain.cpp according to the used COMPort.  
Ensure you have read/write access to the COMPort using admin rights:  

``sudo ./PulseOximeterProvider``  

Or by adding the user to the dialout group:  

``sudo adduser your_user_name dialout``  
``sudo reboot``    
``./PulseOximeterProvider``  

Ensure the pulse oximeter is already running and connected to the "patient" before starting the application.  
Once the finger is removed from the pulse oximeter the pulse oximeter will turn off. In this case the provider application has to be restarted.

