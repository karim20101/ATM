#include "../LIB/STD_TYPES.h"
#include "../MCAL/TWI/TWI_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/GIE/GIE_interface.h"

#include "../HAL/EEPROM/EEPROM_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

u16 location=0;
u8 globalkey='0';

typedef struct {
	u8 name[17];
	u8 password[6];
	u16 money;
}customer;

void login();
void withdraw(u16 arg){
	    u16 funds;
	    u8  local1= EEPROM_u8ReadDataByte(arg);
	    u16 local2=EEPROM_u8ReadDataByte(arg+5);
	    u8 amount[12];
	    u8 c=0;

	    funds= local1 | (local2<<8);
	    MUART_voidSendString ((u8 *)"\r\nenter the amount u want to withdraw :");

	    while(1){

	     amount[c]=  MUART_u8ReadByteSynchBlocking ();
	     _delay_ms(5);
	     if(amount[c]=='#'){
	    	 break;
	     }
	     c++;
	    }


	        int i = 0;

	        // Traversing string
	        for (int j=0;j<c;j++) {
	            // Checking if the element is number
	            if (amount[j] >= '0' && amount[j]  <= '9') {
	                i = i * 10 + (amount[j]  - '0');
	            }
	            // Otherwise print bad output
	            else {


	            }
	        }





	    if(funds<i){
	    	MUART_voidSendString ((u8 *)"\r\nyour Balance is not enough ");
	    }
	    else{
	    	funds-=i;
	    	MUART_voidSendString ((u8 *)"\r\nprocess succeeded ");
	    	  local1= funds;
	    	  local2=funds>>8;
	    	  EEPROM_voidSendDataByte(arg,local1);
	    	  EEPROM_voidSendDataByte((arg+5),local2);


	    	MUART_voidSendString ((u8 *)"\r\nur current balance is:");
	    	 u32 local_u32Number = 1;
	    	  if (funds == 0)
	    	  {
	    		  MUART_voidSendString((u8 *)'0');
	    	  }
	    	  else
	    	  {
	    		  while (funds != 0)
	    		  {
	             local_u32Number = ((local_u32Number*10)+(funds%10));
	    			  funds = funds / 10;
	    		  }
	    		  while (local_u32Number !=1)
	    		  {
	    			  MUART_voidSendByteAsynch((local_u32Number%10)+48);
	    			  _delay_ms(5);
	    			  local_u32Number = local_u32Number /10;
	    		  }
	    	  }






	    }

}


void inquiry(u16 arg){
	    u16 funds;
	    u8 local1= EEPROM_u8ReadDataByte(arg);
	    u16 local2=EEPROM_u8ReadDataByte(arg+5);

//	    u8 c=0;

	    funds= local1 | (local2<<8);



	    	MUART_voidSendString ((u8 *)"\r\nur current balance is:");
	    	_delay_ms(10);
	    	 u32 local_u32Number = 1;
	    	  if (funds == 0)
	    	  {
	    		  MUART_voidSendString((u8 *)"zero \r\n");
	    	  }
	    	  else
	    	  {

	    		  while (funds != 0)
	    		  {
	    			  local_u32Number = ((local_u32Number*10)+(funds%10));
	    			  funds = funds / 10;
	    		  }
	    		  while (local_u32Number !=1)
	    		  {
	    			  MUART_voidSendByteAsynch((local_u32Number%10)+48);
	    			  _delay_ms(5);
	    			  local_u32Number = local_u32Number /10;
	    		  }
	    	  }


	    }






void registration(){



    u8 local1=  EEPROM_u8ReadDataByte(1005);
	 _delay_ms(100);


    u16 local2=EEPROM_u8ReadDataByte(1010);
    _delay_ms(100);
    location= local1 | (local2<<8);

    if(location<1000){

        customer cus;
        s8 counter=0;

    	MUART_voidSendString ((u8 *)"enter username:");
    	while(1){
    		cus.name[counter]= MUART_u8ReadByteSynchBlocking ();

    		if(cus.name[counter]=='#' ){
    			counter=0;
    		 	break;
    		                           }
    		if(cus.name[counter]== 8){
    		    			counter--;
    		    		 	continue;
    		    		               }
    		if(counter>=17){
    			MUART_voidSendString ((u8 *)" \r\nthe name is long please enter the name again");
    			MUART_voidSendString ((u8 *)"\r\nenter username:");
    			counter =-1;
    		               }
             counter++;
    	      }

    	MUART_voidSendString ((u8 *)"\r\nenter password of five numbers:");
    		while(1){
    			cus.password[counter]= MUART_u8ReadByteSynchBlocking ();

    			if(cus.password[counter]=='#'){
    				counter=0;
    			 	break;
    			                           }

    			if(cus.password[counter]== 8){
    			    		    			counter--;
    			    		    		 	continue;
    			    		    		               }
    			if(counter>=6){
    						MUART_voidSendString ((u8 *)"\r\nthe password is long please enter the name again ");
    						MUART_voidSendString ((u8 *)"\r\nenter password:");
    						counter =-1;
    					               }
    	         counter++;
    		      }

    		while(counter<17){

    			 EEPROM_voidSendDataByte(location, cus.name[counter]);
    			 _delay_ms(5);
    			 counter++;
    			 location+=5;

    		}

         counter=0;
    		while(counter<6){

    					 EEPROM_voidSendDataByte(location, cus.password[counter]);
    					 _delay_ms(5);
    					 counter++;
    					 location+=5;
    				}

    		 EEPROM_voidSendDataByte(location, 200);
    		 _delay_ms(5);
    		 location+=5;
    		 		 EEPROM_voidSendDataByte(location, 0);
    		 		 _delay_ms(5);
    		 		 location+=5;
    		EEPROM_voidSendDataByte(1005, (u8)location);
    		_delay_ms(5);

    		EEPROM_voidSendDataByte(1010, (u8)(location>>8));

    		MUART_voidSendString ((u8 *)"\r\n your registration process is succeeded");
    }else{
    	 MUART_voidSendString ((u8 *)"\r\n the memory is full so u can not add another customer");
    }



	}




void login(){

	    customer cus;
	    s8 counter=0;
	    u8 LC=0;
	    u16 GC=0;
	    u8 flag=0;
	    u8 flag2=0;
	    u8 flag3=0;
	    u8 flag4=0;
	    u8 process;


		MUART_voidSendString ((u8 *)"\r\nenter username:");
		while(1){
			cus.name[counter]= MUART_u8ReadByteSynchBlocking ();


			if(cus.name[counter]=='#' ){
				counter=0;
			 	break;
			                           }
			if(cus.name[counter]==8){
				counter--;
							continue;
						               }


			if(counter>=17){
				MUART_voidSendString ((u8 *) "\r\nthe name is long please enter the name again");
				MUART_voidSendString ((u8 *)"\r\nenter username:");
				counter =-1;
			               }
	         counter++;
		      }
		MUART_voidSendString ((u8 *)"\r\n enter password of five numbers:");
			while(1){
				cus.password[counter]= MUART_u8ReadByteSynchBlocking ();


				if(cus.password[counter]=='#'){
					counter=0;
				 	break;
				                           }
				if(cus.password[counter]==8){
					counter--;
									continue;
								               }
				if(counter>=6){
							MUART_voidSendString ((u8 *)"the password is long please enter the name again \r\n");
							MUART_voidSendString ((u8 *)"enter password:");
							counter =-1;
						               }
		         counter++;
			      }


	   while(flag3 ==0 ){

		   while (EEPROM_u8ReadDataByte(GC) != '#'){

			   if(cus.name[LC] != EEPROM_u8ReadDataByte(GC) ){

				   flag=1;
				   break;
			   }
			   LC++;
			   GC+=5;

		   }


		   if(flag ==1){
			   GC+=(25*5)-(LC*5);
			   LC=0;

			   flag=0;
			   if(GC>999){
			   			   MUART_voidSendString ((u8 *)"\r\nthe user name not correct");
			   			   flag3=1;
			   			   break;
			   		   }

		   }

		   else{
			   GC+=(17*5)-(LC*5);
			   LC=0;
			   flag4=1;
//			   MUART_voidSendString ((u8 *)"c");
		      break;
		   }

	   }
//			 MUART_voidSendString ((u8 *)"end1");
       if (flag4==1){
			  while (EEPROM_u8ReadDataByte(GC) != '#'){
						   if(cus.password[LC] != EEPROM_u8ReadDataByte(GC) ){
								   flag2=1;
								   break;
						   	   	}
						   LC++;
						   GC+=5;
					   }
			if(flag2==1){
				MUART_voidSendString ((u8 *)"\r\npassword is not correct");
			}
			else{
				GC+=5;
				globalkey='1';
			}

			while(globalkey == '1'){
				MUART_voidSendString ((u8 *)"\r\n enter w for withdraw process or e for enquiry or 0 for exit  \r\n");
			  process=   MUART_u8ReadByteSynchBlocking ();
				switch(process){

				case 'w': withdraw(GC);

				          break;

				case 'e':inquiry(GC);

		                 break;
				case '0': globalkey='0';

				          break;

				default :
					MUART_voidSendString ((u8 *)"\r\n wrong selection ");
					break;

				}
			}

}
       MUART_voidSendString ((u8 *)"\r\nend of process  ");
}

void test(void){
	 EEPROM_voidSendDataByte(1005,0);
     _delay_ms(10);
     EEPROM_voidSendDataByte(1010,0);
         _delay_ms(50);




}

void deposit (void){

    customer cus;
	    s8 counter=0;
	    u8 LC=0;
	    u16 GC=0;
	    u8 flag=0;
	    u8 flag2=0;
	    u8 flag3=0;
	    u8 flag4=0;



		MUART_voidSendString ((u8 *)"\r\nenter username:");
		while(1){
			cus.name[counter]= MUART_u8ReadByteSynchBlocking ();


			if(cus.name[counter]=='#' ){
				counter=0;
			 	break;
			                           }
			if(cus.name[counter]== 8){
			    		    			counter--;
			    		    		 	continue;
			    		    		               }
			if(counter>=17){
				MUART_voidSendString ((u8 *) "\r\nthe name is long please enter the name again");
				MUART_voidSendString ((u8 *)"\r\nenter username:");
				counter =-1;
			               }
	         counter++;
		      }
		MUART_voidSendString ((u8 *)"\r\nenter password of five numbers:");
			while(1){
				cus.password[counter]= MUART_u8ReadByteSynchBlocking ();


				if(cus.password[counter]=='#'){
					counter=0;
				 	break;
				                           }
				if(cus.password[counter]== 8){
				    		    			counter--;
				    		    		 	continue;
				    		    		               }
				if(counter>=6){
							MUART_voidSendString ((u8 *)"\r\nthe password is long please enter the name again");
							MUART_voidSendString ((u8 *)"\r\nenter password:");
							counter =-1;
						               }
		         counter++;
			      }


	   while(flag3 ==0 ){

		   while (EEPROM_u8ReadDataByte(GC) != '#'){

			   if(cus.name[LC] != EEPROM_u8ReadDataByte(GC) ){

				   flag=1;
				   break;
			   }
			   LC++;
			   GC+=5;

		   }


		   if(flag ==1){
			   GC+=(25*5)-(LC*5);
			   LC=0;

			   flag=0;
			   if(GC>999){
			   			   MUART_voidSendString ((u8 *)"\r\nthe user name not correct");
			   			   flag3=1;
			   			   break;
			   		   }

		   }

		   else{
			   GC+=(17*5)-(LC*5);
			   LC=0;
			   flag4=1;

		      break;
		   }

	   }

       if (flag4==1){
			  while (EEPROM_u8ReadDataByte(GC) != '#'){
						   if(cus.password[LC] != EEPROM_u8ReadDataByte(GC) ){
								   flag2=1;
								   break;
						   	   	}
						   LC++;
						   GC+=5;
					   }
			if(flag2==1){
				MUART_voidSendString ((u8 *)"\r\npassword is not correct");
			}
			else{
				GC+=5;
				globalkey='1';

		     	}
			if(globalkey=='1'){

				        u16 funds;
					    u8 local1= EEPROM_u8ReadDataByte(GC);
					    u16 local2=EEPROM_u8ReadDataByte(GC+5);
					    u8 amount[12];
					    u8 c=0;

					    funds= local1 | (local2<<8);
					    MUART_voidSendString ((u8 *)"\r\nenter the amount u want to deposit :");

					    while(1){

					     amount[c]=  MUART_u8ReadByteSynchBlocking ();
					     _delay_ms(5);
					     if(amount[c]=='#'){
					    	 break;
					     }
					     c++;
					    }


					        int i = 0;

					        // Traversing string
					        for (int j=0;j<c;j++) {
					            // Checking if the element is number
					            if (amount[j] >= '0' && amount[j]  <= '9') {
					                i = i * 10 + (amount[j]  - '0');
					            }
					            // Otherwise print bad output
					            else {


					            }
					        }







					    	funds+=i;


					    	MUART_voidSendString ((u8 *)"\r\nprocess succeeded \n");
					    	  local1= funds;
					    	  local2=funds>>8;
					    	  EEPROM_voidSendDataByte(GC,local1);
					    	  EEPROM_voidSendDataByte((GC+5),local2);


					    	MUART_voidSendString ((u8 *)"\r\nur current balance is:");
					    	 u32 local_u32Number = 1;
					    	  if (funds == 0)
					    	  {
					    		  MUART_voidSendString((u8 *)'0');
					    	  }
					    	  else
					    	  {
					    		  while (funds != 0)
					    		  {
					             local_u32Number = ((local_u32Number*10)+(funds%10));
					    			  funds = funds / 10;
					    		  }
					    		  while (local_u32Number !=1)
					    		  {
					    			  MUART_voidSendByteAsynch((local_u32Number%10)+48);
					    			  _delay_ms(5);
					    			  local_u32Number = local_u32Number /10;
					    		  }
					    	  }



			}
}}

int main(void)
{
	MDIO_voidInit();
	TWI_voidInitMaster(0);
	MUART_voidInit();
	MEXTI_voidSetCfg (EXTI0,FALLING_EDGE);
	MEXTI_voidSetCfg (EXTI1,FALLING_EDGE);
	MEXTI_voidSetCfg (EXTI2,FALLING_EDGE);
	MEXTI_voidSetCallback (EXTI0,&login);
	MEXTI_voidSetCallback (EXTI1,&registration);
	MEXTI_voidSetCallback (EXTI2,&deposit);
	MEXTI_voidEnableINT (EXTI0);
	MEXTI_voidEnableINT (EXTI1);
	MEXTI_voidEnableINT (EXTI2);  
  GIE_voidEnableGlobalInterrupt();





	while(1)
	{

	}
}
