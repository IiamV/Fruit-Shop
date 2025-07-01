#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
===Admin account===
Username: admin
Password: 123
===================
*/

/* DONE
- 2 roles: Admin, Customers (Relogin)
- 0 goto
- Taken names
- All the must have functions
- Design
- Confirmation
*/

/* W.I.P
- Ranges (eg 1-3, 5-8, ...)
- Admin deleles orders
- Password/Name restrictions
*/

struct User {
	char UserName[50];
	char Password[50];
} NewUser, ExistingUser;

struct Fruit{
    char name[30];
    char region[30];
    float price;
};

int LoginAttempt=0;
const char AdminN[] ="admin";
const char AdminP[] ="123";
char CurrentUser[50];
char buffer[100];

FILE *SignupFile;
FILE *LoginFile;
FILE *AdminViewOrdersFile;
FILE *CustomerPrintOrdersFile;

void colorReset() {
	printf("\033[0m");
}

void colorGreen() {
	printf("\033[0;32m");
}

void colorRed() {
    printf("\033[1;31m");
}
void colorYellow () {
    printf("\033[1;33m");
}

int Newpage(int length, int depth) {
	int i;
    for(i=0;i<length;i++)
        printf("\n");
	for(i=0;i<depth;i++)
        printf("\t");
}

void exitfromcode() {
	printf("\033[1;33m");
	Newpage(35,8);
	printf("__| |___________________| |__");
	Newpage(1,8);
	printf("__   ___________________   __");
	Newpage(1,8);
	printf("  | | ____              | |  ");
	Newpage(1,8);
	printf("  | || __ ) _   _  ___  | | ");
	Newpage(1,8);
	printf("  | ||  _ \\| | | |/ _ \\ | |  ");
	Newpage(1,8);
	printf("  | || |_) | |_| |  __/ | | ");
	Newpage(1,8);
	printf("  | ||____/ \\__, |\\___| | | ");
	Newpage(1,8);
	printf("  | |       |___/       | |  ");
	Newpage(1,8);
	printf("__| |___________________| |__");
	Newpage(1,8);
	printf("__   ___________________   __");
	Newpage(1,8);
	printf("  | |                   | |  ");
	printf("\033[0m");
	exit(0);
}

void Signup() { //signup
    char existingUserName[50];
    int usernameTaken=0;
    Newpage(2, 8);
    printf("Enter a username: ");
    scanf("%s", NewUser.UserName);
    Newpage(1, 8);
    printf("Enter a password: ");
    scanf("%s", NewUser.Password);
    SignupFile = fopen("users.txt", "a");
    fclose(SignupFile);
    if (SignupFile != NULL) {
        if (strcmp(NewUser.UserName, AdminN) == 0) {
        	fclose(SignupFile);
        	printf("\033[1;31m");
        	Newpage(2, 8);
            printf("Username is already taken");
            printf("\033[0m");
        } else {
        	rewind(SignupFile);
            while (fscanf(SignupFile, "%s", existingUserName) != EOF) {
                if (strcmp(NewUser.UserName, existingUserName) == 0) {
                    usernameTaken = 1;
                    break;
                }
            }
            if (usernameTaken==1) {
            	printf("\033[1;31m");
            	Newpage(2, 8);
                printf("Username is already taken.");
                printf("\033[0m");
            } else {
            	SignupFile = fopen("users.txt", "a+");
                fprintf(SignupFile, "%s %s", NewUser.UserName, NewUser.Password);
                printf("\033[0;32m");
                printf("Account registered.");
                printf("\033[0m");
            }
		    fclose(SignupFile);
        }
    } else {
    	printf("\033[1;31m");
        Newpage(1,7);
	    printf("File Error\n");
	    printf("\033[0m");
	}
} //signup

void Signin() { //signin
    char OldName[50];
    char OldPassword[50];
    Newpage(2, 8);
    printf("Enter your username: ");
    scanf("%49s", OldName);
    Newpage(0, 8);
    printf("Enter your password: ");
    scanf("%49s", OldPassword);
    
    if (strcmp(OldName, AdminN) == 0 && strcmp(OldPassword, AdminP) == 0) {
    	strcpy (CurrentUser, AdminN);
    	printf("\033[0;32m");
    	Newpage(35, 8);
        printf("Welcome, %s\n", CurrentUser);
        printf("\033[0m");
        LoginAttempt=1;
    }
	else {
		LoginFile = fopen("users.txt", "a");
		fclose(LoginFile);
        if (LoginFile != NULL) {
        	LoginFile = fopen("users.txt", "r");
        	rewind(LoginFile);
            while (fscanf(LoginFile, "%49s %49s", ExistingUser.UserName,ExistingUser.Password) !=EOF) {
                if (strcmp(ExistingUser.UserName, OldName) ==0 && strcmp(ExistingUser.Password, OldPassword) == 0) {
                	strcpy (CurrentUser, ExistingUser.UserName);
                    fclose(LoginFile);
                    printf("\033[0;32m");
                    Newpage(35, 8);
                    printf("Greetings, customer %s\n", CurrentUser);
                    printf("\033[0m");
                    LoginAttempt=1;
                }
	        }
	        fclose(LoginFile);
        }
        else {
        	printf("\033[1;31m");
        	Newpage(1,7);
        	printf("Error Opening File");
        	printf("\033[0m");
		}
    }
} //signin

void displayFruits(Fruit fruits[], int numFruits) {
	Newpage(2,6);
    printf("Available Fruits: \n");
    for (int i = 0; i < numFruits; i++) {
    	Newpage(0,7);
        printf("%d. %s (%s) - $%.2f\n", i + 1, fruits[i].name, fruits[i].region, fruits[i].price);
    }
}

void displayRegions(Fruit fruits[], int numFruits) {
	Newpage(1,7);
    printf("Available Regions:\n");
    for (int i = 0; i < numFruits; i++) {
    	Newpage(0, 7);
        printf("%d. %s\n", i + 1, fruits[i].region);
    }
}

void displayCart(Fruit fruits[], int cart[], int cartSize) {
    float totalPrice=0.0;
    Newpage(2,6);
    printf("Selected Fruits in the Cart: ");
    for (int i = 0; i < cartSize; i++) {
        int index = cart[i];
        Newpage(1,7);
        printf("%d. %s (%s) - $%.2f", i+1, fruits[index].name, fruits[index].region, fruits[index].price);
        totalPrice += fruits[index].price;
    }
    printf("\033[0;32m");
    Newpage(2,7);
    printf("Total Price: $%.2f", totalPrice);
    printf("\033[0m");
}

void addToCart(Fruit fruits[], int numFruits, int cart[], int *cartSize) {
    int fruitIndex;
    char userInput[2]; // for wrong input
    Newpage(2,7);
    printf("Enter the number of the fruit to add to the cart (0 to finish): ");
    scanf("%s", userInput);

    while (strcmp(userInput, "0") != 0) {
        fruitIndex = atoi(userInput);
        if (fruitIndex < 1 || fruitIndex > numFruits) {
        	Newpage(1,8);
            printf("Invalid fruit number. Please try again.\n");
        } else {
            cart[*cartSize] = fruitIndex - 1;
            (*cartSize)++;
            Newpage(1,7);
            printf("%s added to the cart.\n", fruits[fruitIndex - 1].name);
        }
        Newpage(0,6);
        scanf("%s", userInput);
    }
}

void addFruit(Fruit fruits[], int *numFruits) {
	Newpage(1, 7);
    printf("Enter the name of the new fruit: ");
    scanf("%s", fruits[*numFruits].name);
    Newpage(1, 7);
    printf("Enter the region of the new fruit: ");
    scanf("%s", fruits[*numFruits].region);
    Newpage(1, 7);
    printf("Enter the price of the new fruit: ");
    scanf("%f", &fruits[*numFruits].price);
    (*numFruits)++;
}

void removeFromCart(int cart[], int *cartSize) {
    if (*cartSize == 0) {
    	Newpage(1, 7);
        printf("The cart is empty. No fruits to remove.\n");
    }

    int indexToRemove;
    Newpage(1, 6);
    printf("Enter the index of the fruit to remove from the cart (1 to %d): ", *cartSize);
    while (scanf ("%d", &indexToRemove)!=1) {
			colorRed();
			Newpage(1, 8);
			printf ("Invalid option. Please choose again");
			colorReset();
			while (getchar()!='\n');
		}

    if (indexToRemove < 1 || indexToRemove > *cartSize) {
    	Newpage(1, 7);
        printf("Invalid index. Please enter a valid index to remove a fruit.\n");
    } else {
    	Newpage(1, 6);
        printf("Removing fruit with the index %d from the cart.\n", indexToRemove);
        for (int i = indexToRemove - 1; i < *cartSize - 1; ++i) {
            cart[i] = cart[i + 1];
        }
        (*cartSize)--;
    }
}

int main() {
	char confirmation[10];
	int LoginMenuChoice;
	int AdminMenuChoice;
	int AdminInnerChoice;
	int CustomerMenuChoice;
	int CustomerInnerMenuChoice;
	int cartSize=0, cart[30];
	Fruit fruits[] = {{"Apple", "North America", 1.15},
                      {"Pineapple", "Africa", 5.40},
                      {"Cabbage", "Europe", 1.25},
					  {"Mango", "Asia", 7.00}};
    int numFruits = sizeof(fruits) / sizeof(fruits[0]);
	    colorYellow();
	    Newpage(0,7);
	    printf(" _____                                    _____ ");
	    Newpage(1,7);
	    printf("( ___ )                                  ( ___ )");
	    Newpage(1,7);
	    printf(" |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | ");
	    Newpage(1,7);
	    printf(" |   |    _   _          _   _            |   | ");
	    Newpage(1,7);
	    printf(" |   |   | | | |   ___  | | | |   ___     |   | ");
	    Newpage(1,7);
	    printf(" |   |   | |_| |  / _ \\ | | | |  / _ \\    |   | ");
	    Newpage(1,7);
	    printf(" |   |   |  _  | |  __/ | | | | | (_) |   |   | ");
	    Newpage(1,7);
	    printf(" |   |   |_| |_|  \\___| |_| |_|  \\___/    |   | ");
	    Newpage(1,7);
	    printf(" |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| ");
	    Newpage(1,7);
	    printf("(_____)                                  (_____)   "); 
	    colorReset();
	    do { //Login Menu Loop
	    Newpage(1,9);
	    printf ("1.Login");
	    Newpage(1,9);
	    printf("2.Signup");
	    colorRed();
	    Newpage(2,9);
	    printf("3.Exit");
	    colorReset();
	    Newpage(2,9);
		printf ("Choice?: ");
		while (scanf ("%d", &LoginMenuChoice)!=1) {
			colorRed();
			Newpage(1, 8);
			printf ("Invalid option. Please choose again");
			colorReset();
			while (getchar()!='\n');
		}
		switch(LoginMenuChoice) { //switch
			case 1: {
				Signin();
				Newpage(5, 0);
				if (LoginAttempt==1) {
					if ((strcmp(CurrentUser, AdminN))==0) {
					 //Go into admin menu
                		Newpage(1,8);
                		printf ("1.Fruit List");
                		Newpage(1,8);
                		printf("2.Customer's Orders");
                		Newpage(1,8);
                		printf("3.Logout");
                		colorRed();
                		Newpage(1,8);
                		printf("4.Exit");
                		colorReset();
                		do {
                			Newpage(1,7);
                			printf ("Choice?: ");
                			while (scanf ("%d", &AdminMenuChoice)!=1) {
                				colorRed();
                				Newpage(2,7);
                			    printf ("Invalid option. Please choose again");
                			    colorReset;
			                    while (getchar()!='\n');
			                }
           			   		switch (AdminMenuChoice) {//switch
               				    case 1: {
               				    	Newpage(1,8);
    		           		    	printf ("1.View List");
    		           		    	Newpage(1,8);
    		           		    	printf("2.Add item");
    		           		    	Newpage(1,8);
    		           		    	printf("3.Remove item");
    		           		    	Newpage(1,8);
			                        printf("4.Menu");
   			           		    	do { //Fruitlist Inner Menu
   			           		    	    Newpage(2,7);
      		    			    	    printf ("Choice?: ");
	               			    	    while (scanf ("%d", &AdminInnerChoice)!=1) {
	               			    	    	colorRed();
	               			    	    	Newpage(2,7);
                			                printf ("Invalid option. Please choose again");
                			                colorReset();
			                                while (getchar()!='\n');
			                            }
	                    			    switch (AdminInnerChoice) { //switch
			              	    	    	case 1: {
		    	    							displayFruits(fruits, numFruits);
	                							break;
	               							}
	    	            					case 2: {
	        	        						addFruit(fruits, &numFruits);
	                							break;
	            	    					}
	                						case 3: {
	                							
	                							int deleteIndex;
	                							Newpage(1,7);
                                                printf("Enter the index number of an item to remove it");
                                                while (scanf ("%d", &deleteIndex)!=1) {
	               			    	            	colorRed();
	               			    	            	Newpage(2,7);
                			                        printf ("Invalid option. Please choose again");
                			                        colorReset();
			                                        while (getchar()!='\n');
			                                    }
                                                deleteIndex--;
                                                for (int i = deleteIndex; i < numFruits-1; i++) {
                                                    fruits[i] = fruits[i + 1];
                                                }
	                							break;
	                						}
	                						case 4: {
	                							break;
	                						}
	                						default: {
	                							colorRed();
	                							Newpage(1,7);
	                							printf ("Invalid option. Please choose again");
	                							colorReset();
	                							break;
	                						}
	                					} //switch
	                				} while (AdminInnerChoice!=4); //Fruilist Inner Menu
	                	    	
	                			break;
	                		}
	                		case 2: {
	                			Newpage(2,6);
	                			printf ("Customer Orders");
	                			Newpage(2,6);
	                			printf ("Current Orders: \n");
	                			AdminViewOrdersFile= fopen("orders.txt", "a");
	                			fclose(AdminViewOrdersFile);
    	                        if (AdminViewOrdersFile !=NULL) {
    	                        	AdminViewOrdersFile= fopen("orders.txt", "r");
    		                        while (fgets(buffer, sizeof(buffer), AdminViewOrdersFile) != NULL) {
    		                        	Newpage(1,7);
                                        printf("%s", buffer);
                                    }
                                fclose(AdminViewOrdersFile);
                			    }
                		    	break;
                		    }
                			case 3: {
                				int redo = 0;
				                Newpage(2, 8);
                                printf("Confirm?: (");
                                colorGreen();
                                printf("Y");
                                colorReset();
                                printf("/");
                                colorRed();
                                printf("N");
                                colorReset();
                                printf(")");
                                do {
                                    scanf("%9s", confirmation);
                                    getchar();
            
                                    if (strlen(confirmation) == 1) {
                                        if (toupper(confirmation[0]) == 'Y') {
                                            LoginAttempt=0;
                                        }
                                        else if (toupper(confirmation[0]) == 'N') {
                                            redo=0;
                                        }
                                        else {
                                    	    colorRed();
                                    	    Newpage(2, 7);
                                            printf("Invalid confirmation. Please enter Y or N: ");
                                            colorReset();
                                            redo=1;
                                        }
                                    }
                                    else {
                    	                colorRed();
                    	                Newpage(2, 7);
                                        printf("Invalid confirmation. Please enter Y or N: ");
                                        colorReset();
                                        redo=1;
                                    }
                                } while (redo == 1);
                				break;
                			}
                			case 4: {
                				int redo = 0;
				                Newpage(2, 8);
                                printf("Confirm?: (");
                                colorGreen();
                                printf("Y");
                                colorReset();
                                printf("/");
                                colorRed();
                                printf("N");
                                colorReset();
                                printf(")");
                                do {
                                    scanf("%9s", confirmation);
                                    getchar();
            
                                        if (strlen(confirmation) == 1) {
                                            if (toupper(confirmation[0]) == 'Y') {
                                                exitfromcode();
                                            }
                                            else if (toupper(confirmation[0]) == 'N') {
                                                redo=0;
                                            }
                                            else {
                                           	    colorRed();
                                               	Newpage(2, 7);
                                                printf("Invalid confirmation. Please enter Y or N: ");
                                                colorReset();
                                                redo=1;
                                            }
                                        }
                                        else {
                                           	colorRed();
                                           	Newpage(2, 7);
                                            printf("Invalid confirmation. Please enter Y or N: ");
                                            colorReset();
                                            redo=1;
                                        }
                                } while (redo == 1);
                				break;
                			}
                		}//switch
                	} while (LoginAttempt==1);
 				//Go into admin menu
				}
				else { //Go into customer menu
				    Newpage(1,8);
	                printf ("1.Fruit List");
	                Newpage(1,8);
	                printf("2.Current Order");
	                Newpage(1,8);
	                printf("3.Payment");
	                Newpage(1,8);
	                printf("4.Logout");
	                colorRed();
	                Newpage(1,8);
	                printf("5.Exit");
	                colorReset();
	                do {
	                	Newpage(2,7);
	                    printf ("Choice?: ");
    					while (scanf ("%d", &CustomerMenuChoice)!=1) {    						
    						colorRed();
    						Newpage(2,7);
                			printf ("Invalid option. Please choose again");
                			colorReset();
			                while (getchar()!='\n');
			            }
    					switch (CustomerMenuChoice) { //switch
    						case 1: {
    							Newpage(1,8);
    							printf ("1.View List");
    							Newpage(1,8);
    							printf("2.Choose Region");
    							Newpage(1,8);
    							printf("3.Add item to cart");
    							Newpage(1,8);
    							printf("4.Remove item from cart");
    							Newpage(1,8);
    							printf("5.Menu");
    								do { //Fruitlist Inner Menu
    								    Newpage(2,7);
		    	    					printf ("Choice?: ");
		    	    					while (scanf ("%d", &CustomerInnerMenuChoice)!=1) {
		    	    						colorRed();
		    	    						Newpage(2,7);
                			                printf ("Invalid option. Please choose again");
                			                colorReset();
			                                while (getchar()!='\n');
			                            }
		    	    					
		    	    					switch (CustomerInnerMenuChoice) { //switch
		    	    						case 1: {	    	    							
		    	    							displayFruits(fruits, numFruits);
												break;
											}
											case 2: {
												displayRegions(fruits, numFruits);
												int regionIndex;
												Newpage(1,7);
            									printf("Enter the number of the region to search: ");
            									while (scanf ("%d", &regionIndex)!=1) {
		    	    						        colorRed();
		    	    						        Newpage(2,7);
                			                        printf ("Invalid option. Please choose again");
                			                        colorReset();
			                                        while (getchar()!='\n');
			                                    }
            									if (regionIndex < 1 || regionIndex > numFruits) {
            										Newpage(1,7);
            									    printf("Invalid region number. Please try again.\n");
            									} else {
    								            char searchRegion[30];
       									        strcpy(searchRegion, fruits[regionIndex - 1].region);
       									        Newpage(0,7);
                								printf("Fruits in Region '%s':\n", searchRegion);
                								for (int i = 0; i < numFruits; ++i) {
                    								if (strcmp(fruits[i].region, searchRegion) == 0) {
                    									Newpage(0,7);
                    						    		printf("%d. %s (%s) - $%.2f\n", cartSize + 1, fruits[i].name, fruits[i].region, fruits[i].price);
                    						    		cart[cartSize] = i;
                        								(cartSize)++;
                    								}
                								}
            									}
												break;
											}
											case 3: {
												addToCart(fruits, numFruits, cart, &cartSize);
												break;
											}
											case 4: {
												removeFromCart(cart, &cartSize);
												break;
											}
											case 5: {
												// Customer Return to customer menu
												break;
											}
											default: {
												colorRed();
    							                Newpage(2,7);
    						                	printf ("Invalid option. Please choose again");
    							                colorReset();
												break;
											}
										} //switch
									} while (CustomerInnerMenuChoice!=5); //Fruilist Inner Menu
    			
    							break;
    						}
    						case 2: {
    							Newpage(1,8);
    							printf ("Current Order");
    							displayCart(fruits, cart, cartSize);
    							break;
    						}
    						case 3: {
    							int OrderConfirm;
    							Newpage(1,8);
	    						printf ("Payment");
	    						Newpage(1,7);
	    						printf ("User: %s", CurrentUser);
	    						displayCart(fruits, cart, cartSize);
	    						Newpage(1,7);
	    						printf ("Confirm Order? (1:yes\n0:no)");
	    						Newpage(1,7);
	    						printf ("1:yes/2:no");
    	                        while (scanf ("%d", &OrderConfirm)!=1) {
		    	    				colorRed();
		    	    				Newpage(2,7);
                	                printf ("Invalid option. Please choose again");
               		                colorReset();
	                                while (getchar()!='\n');
	                            }
    	                        if (OrderConfirm==1) {
    	                        	CustomerPrintOrdersFile= fopen ("orders.txt", "a");
    	                        	fclose(CustomerPrintOrdersFile);
    		                        if (CustomerPrintOrdersFile !=NULL) {
    		                        	CustomerPrintOrdersFile= fopen ("orders.txt", "a");
    		                            fprintf(CustomerPrintOrdersFile,"\nCustomer: %s", CurrentUser);
    		                            float totalPrice = 0.0;
    		                            Newpage(1,8);
                                        printf("Order:");
                                        for (int i = 0; i < cartSize; ++i) {
                                            int index = cart[i];
                                            fprintf(CustomerPrintOrdersFile,"\n%d. %s (%s) - $%.2f", i + 1, fruits[index].name, fruits[index].region, fruits[index].price);
                                            totalPrice += fruits[index].price;
                                        }
                                        fprintf(CustomerPrintOrdersFile,"Total Price: $%.2f\n", totalPrice);
				                        fprintf (CustomerPrintOrdersFile, "\n");
				                        fclose(CustomerPrintOrdersFile);
				                        colorGreen();
				                        Newpage(2,8);
				                        printf ("Successfully printed order");
				                        colorReset();
    		                        }
    		                        else printf ("File Error");
		                        }
    							break;
    						}
    						case 4: {
    							int redo = 0;
				                Newpage(2, 8);
                                printf("Confirm?: (");
                                colorGreen();
                                printf("Y");
                                colorReset();
                                printf("/");
                                colorRed();
                                printf("N");
                                colorReset();
                                printf(")");
                                do {
                                    scanf("%9s", confirmation);
                                    getchar();
            
                                    if (strlen(confirmation) == 1) {
                                        if (toupper(confirmation[0]) == 'Y') {
                                            LoginAttempt=0;
                                        }
                                        else if (toupper(confirmation[0]) == 'N') {
                                            redo=0;
                                        }
                                        else {
                                        	colorRed();
                                        	Newpage(2, 7);
                                            printf("Invalid confirmation. Please enter Y or N: ");
                                            colorReset();
                                            redo=1;
                                        }
                                    }
                                    else {
                                    	colorRed();
                                    	Newpage(2, 7);
                                        printf("Invalid confirmation. Please enter Y or N: ");
                                        colorReset();
                                        redo=1;
                                    }
                                } while (redo == 1);
    							break;
    						}
    						case 5: {
    							int redo = 0;
				                Newpage(2, 8);
                                printf("Confirm?: (");
                                colorGreen();
                                printf("Y");
                                colorReset();
                                printf("/");
                                colorRed();
                                printf("N");
                                colorReset();
                                printf(")");
                                do {
                                    scanf("%9s", confirmation);
                                    getchar();
            
                                    if (strlen(confirmation) == 1) {
                                        if (toupper(confirmation[0]) == 'Y') {
                                            exitfromcode();
                                        }
                                        else if (toupper(confirmation[0]) == 'N') {
                                            redo=0;
                                        }
                                        else {
                                        	colorRed();
                                        	Newpage(2, 7);
                                            printf("Invalid confirmation. Please enter Y or N: ");
                                            colorReset();
                                            redo=1;
                                        }
                                    }
                                    else {
                                    	colorRed();
                                    	Newpage(2, 7);
                                        printf("Invalid confirmation. Please enter Y or N: ");
                                        colorReset();
                                        redo=1;
                                    }
                                } while (redo == 1);
    							break;
    						}
    						default: {
    							colorRed();
    							Newpage(2,7);
    							printf ("Invalid option. Please choose again");
    							colorReset();
	    						break;
	    					}
	    				} //switch
					} while (LoginAttempt==1);
				} //Go into customer menu
			    } else {
        	        printf("\033[1;31m");
        	        Newpage(2, 7);
		            printf("Login failed. Incorrect username or password.\n");
		            while (getchar()!='\n');
		            printf("\033[0m");
		        }
                break;
			}
			case 2: {
				Signup();
				break;
			}
			case 3: {
				int redo = 0;
				Newpage(2, 8);
                printf("Confirm?: (");
                colorGreen();
                printf("Y");
                colorReset();
                printf("/");
                colorRed();
                printf("N");
                colorReset();
                printf(")");
                do {
                    scanf("%9s", confirmation);
                    getchar();
            
                    if (strlen(confirmation) == 1) {
                        if (toupper(confirmation[0]) == 'Y') {
                            exitfromcode();
                        }
                        else if (toupper(confirmation[0]) == 'N') {
                            redo=0;
                        }
                    else {
                    	colorRed();
                    	Newpage(2, 7);
                        printf("Invalid confirmation. Please enter Y or N: ");
                        colorReset();
                        redo=1;
                    }
                    }
                    else {
                    	colorRed();
                    	Newpage(2, 7);
                        printf("Invalid confirmation. Please enter Y or N: ");
                        colorReset();
                        redo=1;
                    }
                } while (redo == 1);
				break;
			}
			default: {
				colorRed();
				Newpage(2, 8);
				printf ("Invalid option. Please choose again\n");
				colorReset();
				break;
			}
		} //switch
	} while (1); //Login Menu Loop
}
