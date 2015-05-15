This is a basic program to pull up the geolocation of an IP address. This program functions as below:
* It checks whether the user has entered an IP address or not
	Yes: It finds the location (city, country) of the the received IP address.
	No: It finds the location (city, country) of the the machine.

* This is probably the easiest solution to this problem, but not the best one-for sure. 
Generally Using system() should be avoided, but I have used it here considering that: 
-It is not called in any loop.
-Only validated parameters are passed to the function.
