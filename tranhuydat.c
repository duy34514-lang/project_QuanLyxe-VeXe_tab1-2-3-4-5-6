#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
	char name[50];
	char address[100];
} Location ;
typedef struct {
	char name[50] ;
	char phone[15] ; 
} Passenger  ;
typedef struct {
	char tripIdTk[20] ;
	int ticketId ;
	Passenger person ;
	int seatNumber ;
	int price ;
	int paymentStatus ;
	char date[20] ;
} Ticket ;
typedef struct {
	char tripid[20] ;
	Location departure ; //diemdi
	Location destination ; //diemden
	char date[50] ;
	int totalSeats ; //tong so ghe
	int bookedSeats ; //so ghe da dat
} Trip ;
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void setCurrentTime(char *out, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(out, size, "%d/%m/%Y %H:%M:%S", tm_info);
}

int check( char *str , int *ptr ) {
    if (fgets(str, 15, stdin) == NULL) {
        return 0; 
    }
    str[strcspn(str, "\n")] = '\0';
    if (strlen(str) == 14 && str[13] != '\0') {
        clearBuffer();
    }
    if (sscanf(str, "%d", ptr) == 1) {
        return 1;
    } else {
        return 0;
    }
}

void checkString(char *string, int maxLen) {
    while (1) {
        if (fgets(string, maxLen, stdin) == NULL) {
            printf("Nhap khong hop le, nhap lai: ");
            continue;
        }
        string[strcspn(string, "\n")] = '\0';
        int len = strlen(string);
        
        if (len == maxLen - 1 && string[len-1] != '\0' && getchar() != '\n') {
             printf("Nhap qua gioi han %d ky tu, nhap lai: ", maxLen - 1);
             clearBuffer();
             continue;
        }
        
        if (len == 0) {
            printf("Khong duoc rong, nhap lai: ");
            continue;
        }
        if (string[0] == ' ') {
            printf("Khong duoc bat dau bang khoang trang, nhap lai: ");
            continue;
        }
        
        break; 
    }
}

void check15(char *string) { 
    checkString(string, 15); 
	}
void check20(char *string) { 
    checkString(string, 20); 
	}
void check50(char *string) {
    checkString(string, 50); 
	}
void check100(char *string) { 
    checkString(string, 100); 
	}


void output(Trip *CreateNT, int size) {
    int i;
    printf("****************************************************************\n");
    for (i = 0; i < size; i++) {
        printf("*___________________XE %s__________________________\n", CreateNT[i].tripid);
        printf("*|Ten diem di       : %s\n", CreateNT[i].departure.name);
        printf("*|Dia chi diem di    : %s\n", CreateNT[i].departure.address);
        printf("*|Ten diem den       : %s\n", CreateNT[i].destination.name);
        printf("*|Dia chi diem den   : %s\n", CreateNT[i].destination.address);
        printf("*|Ngay/Thang/Nam     : %s\n", CreateNT[i].date);
        printf("*|Tong so ghe        : %d\n", CreateNT[i].totalSeats);
        printf("*----------------------------------------------------------\n");
    }
    printf("****************************************************************\n");
}

void createNewTrip(Trip *CreateNT, int *count) {
    int start, i, j;
    int size ;
    char str[10] ; 
    
    do {
        printf("Ban muon them bao nhieu tuyen: ");
        if (check( str , &size ) == 0) {
            printf("Vui long nhap so nguyen hop le.\n");
            size = 0; 
            continue; 
        }
        if (size <= 0 || *count + size > 100) {
            printf("So tuyen khong hop le, vui long nhap lai.\n");
        }
    } while (size <= 0 || *count + size > 100);

    start = *count;
    *count = *count + size;

    for (i = start; i < *count; i++) {
        printf("Nhap ID xe %d (toi da 19 ky tu): ", i + 1);
        check20(CreateNT[i].tripid);

        for (j = 0; j < i; j++) {
            if (strcmp(CreateNT[i].tripid, CreateNT[j].tripid) == 0) {
                printf("Ma chuyen xe bi trung. Nhap lai ma xe %d: ", i + 1);
                check20(CreateNT[i].tripid);
                j = -1;
            }
        }

        printf("Nhap ten diem di: ");
        check50(CreateNT[i].departure.name);

        printf("Nhap dia chi diem di: ");
        check100(CreateNT[i].departure.address);

        printf("Nhap ten diem den: ");
        check50(CreateNT[i].destination.name);

        printf("Nhap dia chi diem den: ");
        check100(CreateNT[i].destination.address);

        printf("Thoi gian chay: ");
        check20(CreateNT[i].date);
        
        int totalSeats_input;
        
        do {
            printf("Nhap tong so ghe: ");
            if (check( str , &totalSeats_input) == 0) {
                 printf("Vui long nhap so nguyen hop le.\n");
                 totalSeats_input = 0; 
                 continue;
            }
            CreateNT[i].totalSeats = totalSeats_input;
            if (CreateNT[i].totalSeats <= 0)
                printf("So ghe phai > 0\n");
        } while (CreateNT[i].totalSeats <= 0);

        CreateNT[i].bookedSeats = 0;
        printf("\n");
    }

    printf("==> Them %d tuyen thanh cong!\n", size);
}

void update(Trip *CreateNT, int size) {
    int i, k, flag = 0;
    char updateID[20];
    char str[10] ; 
    int totalSeats_input;

    printf("Nhap ID xe can cap nhat: ");
    check20(updateID);

    for (i = 0; i < size; i++) {
        if (strcmp(updateID, CreateNT[i].tripid) == 0) {
            flag = 1;

            do {
                printf("_______________ Cap nhat xe %s ________________\n", CreateNT[i].tripid);
                printf("1. Ten diem di        : %s\n", CreateNT[i].departure.name);
                printf("2. Dia chi diem di     : %s\n", CreateNT[i].departure.address);
                printf("3. Ten diem den        : %s\n", CreateNT[i].destination.name);
                printf("4. Dia chi diem den     : %s\n", CreateNT[i].destination.address);
                printf("5. Ngay thang nam      : %s\n", CreateNT[i].date);
                printf("6. Tong so ghe         : %d\n", CreateNT[i].totalSeats);
                printf("7. Thoat cap nhat\n");
                printf("Ban muon cap nhat muc nao? ");

                do {
                    if (check( str , &k ) == 0) {
                        printf("Vui long nhap so nguyen hop le.\n");
                        k = 0; 
                        continue;
                    }
                    break;
                } while(1);

                switch (k) {
                    case 1:
                        printf("Nhap ten moi: ");
                        check50(CreateNT[i].departure.name);
                        break;

                    case 2:
                        printf("Nhap dia chi moi: ");
                        check100(CreateNT[i].departure.address);
                        break;

                    case 3:
                        printf("Nhap ten diem den moi: ");
                        check50(CreateNT[i].destination.name);
                        break;

                    case 4:
                        printf("Nhap dia chi diem den moi: ");
                        check100(CreateNT[i].destination.address);
                        break;

                    case 5:
                        printf("Nhap ngay/thang/nam moi: ");
                        check20(CreateNT[i].date);
                        break;

                    case 6:
                        do {
                            printf("Nhap so ghe moi: ");
                            if (check( str , &totalSeats_input) == 0) {
                                 printf("Vui long nhap so nguyen hop le.\n");
                                 totalSeats_input = 0;
                                 continue;
                            }
                            CreateNT[i].totalSeats = totalSeats_input;
                            if (CreateNT[i].totalSeats <= 0)
                                printf("So ghe phai > 0\n");
                        } while (CreateNT[i].totalSeats <= 0);
                        break;
                }

            } while (k != 7);

            break;
        }
    }

    if (flag) printf("Cap nhat thanh cong!\n");
    else printf("Khong tim thay ID xe.\n");
}

void bookTicket(Trip *CreateNT, Ticket *ticket, int size, int *countTk) {
	int k ;
    char search[20];
    int i, flag = 0, j = *countTk;
    char str[10] ; 
    int seat_input, price_input;

    do {
        printf("Nhap ma chuyen xe: ");
        check20(search); 
        
        break;
    } while (1);

    for (i = 0; i < size; i++) {
        if (strcmp(search, CreateNT[i].tripid) == 0) {
            flag = 1;

            if (CreateNT[i].bookedSeats >= CreateNT[i].totalSeats) {
   				 printf("Chuyen xe %s da het ghe.\n", CreateNT[i].tripid);
   				 return;
			}
			ticket[j].ticketId = j + 1;
            strcpy(ticket[j].tripIdTk, CreateNT[i].tripid);
            do {
                printf("Nhap ten khach hang: ");
                check50(ticket[j].person.name); 
                break;
            } while (1);
            do {
                printf("Nhap so dien thoai khach hang: ");
                check15(ticket[j].person.phone); 
                
                int len = strlen(ticket[j].person.phone);
                int onlyDigits = 1;
                for ( k = 0; k < len; k++) {
                    if (ticket[j].person.phone[k] < '0' || ticket[j].person.phone[k] > '9') {
                        onlyDigits = 0;
                        break;
                    }
                }
                if (onlyDigits == 0) {
                    printf("Chi duoc nhap so, nhap lai.\n");
                    continue;
                }
                break;
            } while (1);
            do {
            	if ( CreateNT[i].totalSeats == 0 ) {
            		printf ("da het ghe : ") ;
            		break ;
				}
                printf("Xe %s con %d ghe.\n", CreateNT[i].tripid, CreateNT[i].totalSeats - CreateNT[i].bookedSeats);
                printf("Ban muon dat bao nhieu ghe: ");
                
                if (check( str , &seat_input) == 0) {
                    printf("Vui long nhap so nguyen hop le.\n");
                    seat_input = 0; 
                    continue;
                }
                
                if (seat_input <= 0 || seat_input > (CreateNT[i].totalSeats - CreateNT[i].bookedSeats)) {
                    printf("Lua chon khong hop le, nhap lai.\n");
                    continue;
                }

                ticket[j].seatNumber = seat_input;
                CreateNT[i].bookedSeats += seat_input; 
                break;
            } while (1);

            ticket[j].paymentStatus = 0;
            setCurrentTime(ticket[j].date, sizeof(ticket[j].date));
            do {
                printf("Moi ban nhap gia ve: ");
                 if (check( str , &price_input) == 0) {
                    printf("Vui long nhap so nguyen hop le.\n");
                    price_input = -1; 
                    continue;
                }
                ticket[j].price = price_input;
                if (ticket[j].price < 0) printf("Gia ve khong hop le, nhap lai.\n");
            } while (ticket[j].price < 0);

            printf("\n================= Dat ve thanh cong ===============\n");
            printf("Ma chuyen xe   : %s\n", ticket[j].tripIdTk);
            printf("Ho Ten KH      : %s\n", ticket[j].person.name);
            printf("SDT            : %s\n", ticket[j].person.phone);
            printf("So ghe da dat  : %d\n", ticket[j].seatNumber);
            printf("Ngay tao ve    : %s\n", ticket[j].date);
            printf("Gia ve         : %d\n", ticket[j].price);
            printf("Trang thai     : %s\n", ticket[j].paymentStatus == 0 ? "Chua thanh toan" : "Da thanh toan");
            printf("======================================================\n");

            (*countTk)++;
            break;
        }
    }

    if (!flag) {
        printf("Khong co chuyen xe ban tim, vui long chon lai.\n");
    }
}

void CheckTicketStatus(Ticket *ticket, int countTk, Trip *CreateNT, int countTrip) {
	int i , j ;
    if (countTk == 0) {
        printf("Chua co ve nao duoc dat.\n");
        return;
    }
    int searchTk;
    char str[10] ; 
    do {
        printf("Nhap so ve ban muon tim: ");
        if (check( str , &searchTk) == 0) {
            printf("Vui long nhap so hop le: ");
            searchTk = 0;
            continue;
        }
        break;
    } while (1);

    int found = 0;
    for ( i = 0; i < countTk; i++) {
        if (ticket[i].ticketId == searchTk) {
            found = 1;
            
            printf("\n=============================================================\n") ;
            printf("_____________________ Thong tin ve ____________________________\n");
            printf("| Ma chuyen xe   : %s\n", ticket[i].tripIdTk);
            printf("| Ho Ten KH      : %s\n", ticket[i].person.name);
            printf("| SDT            : %s\n", ticket[i].person.phone);
            printf("| So ghe da dat  : %d\n", ticket[i].seatNumber);
            printf("| Ngay tao ve    : %s\n", ticket[i].date);
            printf("| Gia ve         : %d\n", ticket[i].price);
            printf("| Trang thai     : %s\n", ticket[i].paymentStatus == 0 ? "Chua thanh toan" : "Da thanh toan");
            printf("|______________________________________________________________\n") ;
            for ( j = 0; j < countTrip; j++) {
                if (strcmp(ticket[i].tripIdTk, CreateNT[j].tripid) == 0) {
                    printf("|_____________________ Thong tin chuyen xe ______________________\n");
                    printf("| Ten diem di       : %s\n", CreateNT[j].departure.name);
                    printf("| Dia chi diem di   : %s\n", CreateNT[j].departure.address);
                    printf("| Ten diem den      : %s\n", CreateNT[j].destination.name);
                    printf("| Dia chi diem den  : %s\n", CreateNT[j].destination.address);
                    printf("| Ngay/Thang/Nam    : %s\n", CreateNT[j].date);
                    printf("| Tong so ghe       : %d\n", CreateNT[j].totalSeats);
                    printf("| Ghe da dat        : %d\n", CreateNT[j].bookedSeats);
                    printf("|________________________________________________________________\n") ;
                    break;
                }
            }
            
            printf("=======================================================\n");
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay ve co so %d.\n", searchTk);
    }
}

void listTrips ( Trip *CreateNT , int size ) {
	int pageNumber ;
	int pageSize ;
	int i ;
	char str[50] ;
	int totalPages ;
	int choice ;
	printf ("so luong xe 1 trang la : ") ;
	do {
		if ( check ( str , &pageSize ) == 0 ) {
			printf ("vui long nhap dung : ") ;
			continue ;
		}
		break ;
	} while (1) ;
	totalPages = (size + pageSize - 1) / pageSize;
	printf ("ban muon toi trang bao nhieu : ") ;
	do {
		if ( check ( str , &pageNumber ) ) {
			if ( pageNumber > totalPages ) {
			printf ("khong co trang %d " , pageNumber ) ;
			}
		}
	} while ( pageNumber > totalPages ) ;
	do {
		printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n") ;
		for ( i = ( pageNumber - 1 ) * pageSize ; i < size && i < pageNumber*pageSize ; i++  ) {
			printf ("+------------------------------------------------------------------------------------------------------------------------+\n") ;
			printf ("+ Ma so xe         : %-100s+\n" , CreateNT[i].tripid ) ;
			printf ("+ Dia chi diem di  : %-100s+\n" , CreateNT[i].departure.address ) ;
			printf ("+ Dia chi diem den : %-100s+\n" , CreateNT[i].destination.address ) ;
			printf ("+ So ghe da dat / tong so ghe   : %-3d/ %-3d                                                                              +\n" , CreateNT[i].bookedSeats , CreateNT[i].totalSeats ) ;
			printf ("+------------------------------------------------------------------------------------------------------------------------+\n") ;
		}
		printf ("+                   BEFORE (1)                                                           AFTER (2)                       +\n") ;
		printf ("+          HOME (3)                                                                                                      +\n") ;
		printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n") ;
		do {
    		if ( check(str, &choice) == 0 ) {  
      			printf("Nhap sai, vui long nhap lai: ");
       			continue;                       
    		}
    		int temp = pageNumber;
    		if ( choice == 1 ) {
        		pageNumber--;
    		} else if ( choice == 2 ) {
        		pageNumber++;
    		} else if ( choice == 3 ) {
        		return;
    		} else {
        		printf("Chi duoc nhap 1,2,3. Nhap lai: ");
        		continue;
    		}
    		if ( pageNumber < 1 || pageNumber > totalPages ) {
        		printf("Khong con trang de hien thi, vui long chon lai: ");
        		pageNumber = temp;
        		continue;
    		}
    		break; 
		} while (1);
	} while ( choice == 1 || choice == 2 ) ;
}

void updateTicket ( Ticket *ticket , int size ) {
	int i ;
	int flag = 0 ;
	int seach , choice ;
	char str[50] ;
	if ( size == 0 ) {
		printf ("chua co ve nao duoc tao \n") ;
		return;
	}
	printf ("nhap ma ve : ") ;
	while ( check(str, &seach) == 0 ) {
    	printf("Nhap sai, vui long nhap lai ma ve: ");
	}
	for ( i=0 ; i < size ; i++ ) {
		if ( seach == ticket[i].ticketId ) {
			flag = 1 ;
			if ( ticket[i].paymentStatus == 1 ) {
				printf ("ve da duoc thanh toan ( da khoa )!!!") ;
				return ;
			}
			printf ("______________________________________________________________\n") ;
			printf("| Ma chuyen xe   : %s\n", ticket[i].tripIdTk);
            printf("| Ho Ten KH      : %s\n", ticket[i].person.name);
            printf("| SDT            : %s\n", ticket[i].person.phone);
            printf("| So ghe da dat  : %d\n", ticket[i].seatNumber);
            printf("| Ngay tao ve    : %s\n", ticket[i].date);
            printf("| Gia ve         : %d\n", ticket[i].price);
            printf("| Trang thai     : %s\n", ticket[i].paymentStatus == 0 ? "Chua thanh toan" : "Da thanh toan");
            printf("|______________________________________________________________\n") ;
            printf ("Ban muon thanh toan : (1)yesss                     (2)nooo   \n" ) ;
            do {
    		if ( check(str, &choice) == 0 ) { 
      			printf("Nhap sai, vui long nhap lai: ");
       			continue;                       
    		}
    		if ( choice == 1 ) {
        		ticket[i].paymentStatus = 1 ;
        		break ;
    		} else if ( choice == 2 ) {
        		ticket[i].paymentStatus = 0 ;
        		break ;
    		} else {
        		printf("Chi duoc nhap 1,2. Nhap lai: ");
        		continue;
    		} 
			} while (1);
			return ;
		}
	}
	if ( flag == 0 ) printf ("khong tim thay ve !!!!!\n") ;
}
// ================= MAIN ===================
int main() {
    Trip CreateNT[100];
    Ticket ticket[100] ;
    int count = 0, choice ;
    int flag = 0;
    int countTk = 0 ;
    char str[10] ; 

    do {
        printf("___________________________MENU____________________________\n");
        printf("1. Create New Trip\n");
        printf("2. Update Trip Info\n");
        printf("3. Book Ticket\n");
        printf("4. Check Ticket Status\n");
        printf("5. List Trips\n");
        printf("6. Pay Ticket\n");
        printf("7. Lock / Cancel Ticket\n");
        printf("8. Revenue & Ticket Statistics\n");
        printf("____________________________________________________________\n");
        do {
            printf("Nhap lua chon: ") ;
            if (check( str , &choice ) == 0) {
                printf("Vui long nhap so nguyen hop le.\n");
                choice = -1; 
                continue;
            }
            break;
        } while(1);

        switch (choice) {
            case 1:
                flag = 1;
                createNewTrip(CreateNT, &count);
                output(CreateNT, count);
                break;

            case 2:
                if (!flag) {
                    printf("Chua co thong tin chuyen xe!\n");
                    break;
                }
                update(CreateNT, count);
                break;
			case 3:
				if ( flag == 0 ) {
					printf ("chua co thong tin chuyen xe \n") ;
					break ;
				}
				bookTicket( CreateNT, ticket, count , &countTk) ;
				break ;
			case 4:
				if ( flag == 0 ) {
					printf ("chua co thong tin chuyen xe \n") ;
					break ;
				}
				CheckTicketStatus( ticket , countTk, CreateNT, count) ;
				break ;
			case 5:
				if ( flag == 0 ) {
					printf ("chua co thong tin chuyen xe \n") ;
					break ;
				}
				listTrips ( CreateNT , count ) ;
				break ;
			case 6:
				if ( flag == 0 ) {
					printf ("chua co thong tin chuyen xe \n") ;
					break ;
				}
				updateTicket ( ticket , countTk ) ;
				break ;
			case 7:
				if ( flag == 0 ) {
					printf ("chua co thong tin chuyen xe \n") ;
					break ;
				}
				printf("Chuc nang Lock / Cancel Ticket chua duoc trien khai.\n");
				break ;
		    case 8:
		    	if ( flag == 0 ) {
					printf ("chua co thong tin chuyen xe \n") ;
					break ;
				}
				printf("Chuc nang Revenue & Ticket Statistics chua duoc trien khai.\n");
				break ;
            default:
                printf("Lua chon khong hop le.\n");
                break;
		}
	} while ( 1 ) ;
}
