
# <p align="center">About The Project ✨</p>
  
This Garbage Collector is a tool that replaces 'free( )' and 'malloc( )', to allow you to liberate all allocations made all at once.


# <p align="center">Compilation 📝</p>
  
To use the Garbage Collector, you have to go insinde the folder and compiling whit 'make'.
Then compile the 'garbage_collector.a' with others C files to use it.
Dont forget to include 'garbage_collector.h'


# <p align="center">Usage ⚙️</p>

There is 3 function in this library :

 - ft_malloc   : this function works like the real malloc function,  it returns a pointers to an heap allocated zone, of the size precised in parameter. Make sure to use this function at least one time before the others.

- ft_free : this function copy the real 'free( )' function. You can use it on all addresses, wheter they are allocated by the 'ft_malloc( )' function or not.

- destroy_garbage : this function free the garbage and all the addresses allocated by 'ft_malloc( )' but not free'd by 'ft_free( )'. Use it with a NULL parameter. Make sure to use this function at the very end, because the others functions are disabled after that.


## More . . . 😆

If you wanna find more of my [projects](https://photo.capital.fr/musk-25050#the-boring-company-des-tunnels-pour-desengorger-le-trafic-en-ville-434177) .
        
        
    