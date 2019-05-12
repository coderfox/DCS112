# [inhenritance] time & ExtTime _from lecture 4

## description
```
需要实现的是一下两个类，time作为父类，ExtTime作为子类，以下是两个类的声明，你需要做的是，实现这两个类
class  Time
{						
public : 				
       void  Set ( int  hours , int  minutes , int  seconds ) ;
       void  Increment ( ) ;
       void  Write ( )  const ;
       Time ( int  initHrs, int  initMins,  int  initSecs ) ;  // constructor 
       Time ( ) ; 	   //  default constructor

private :				
       int hrs ;           
       int mins ;          
       int	 secs ;
} 
class  ExtTime  :  public  Time	// Time is the base class
{
public :
        ExtTime ( int  initHrs ,  int  initMins ,  int  initSecs ,
		  ZoneType    initZone ) ;      // constructor
        ExtTime ( ) ; 			             // default constructor
        void Set ( int  hours,  int  minutes,  int   seconds ,
                         ZoneType   timeZone ) ;	
        void Write ( )  const ;
        
private :				
	ZoneType  zone ; 	//  added data member
} ;

```