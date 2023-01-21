#include "header.h"  // the project file is deficult to read so i include all metods in my header.h file 


//resive msg and send msg process are common so i have declaier methods for it 
//the child C1 ,C2 ,C3, C4 ,C5 have same work to do so i have use chiledMethod to implement it


int main()
{
	
	struct msg childMsg  = createMsg(100,"Hello my mom    ");

	key_t key_for_MQ = ftok("file2751.txt",99);//creating a key

	MQID = msgget(key_for_MQ,IPC_CREAT|0666);//creating a MQ 

	int PID1,PID2,PID3,PID4,PID5,PID6;

	switch(PID1 = fork()){ //create child 1
		case -1 : // error 
			perror("child1");
			exit(0);
			break;
		case  0 : // child C1
			getpid();
			switch(PID2=fork()){ //create child 2
				case -1:
					perror("child2");
					exit(1);
				break;
				case 0: // child C2
					switch(PID3=fork()){ //create child 3
						case -1:
							perror("child3");
							exit(1);
						break;
						case 0: // child C3
								switch(PID4=fork()){ //create child 4
									case -1:
										perror("child4");
										exit(1);
									break;
									case 0: // child C4
										switch(PID5=fork()){ //create child 5
											case -1:
												perror("child5");
												exit(1);
											break;
											case 0: // child C5
													switch(PID6=fork()){ //create child 6
														case -1:
															perror("child6");
															exit(1);
														break;
														case 0: // child C6
															getpid();
															char p[] = "C6";
															char cmt[] = "Hello my mom Iam Child ";
															strcat(cmt,p);
															struct msg resiveMsg = reciveMsg(p);
															struct msg chiledMsg = createMsg(100,cmt);
															sendMsg(p,chiledMsg);
															printf("Child %s terminated\n",p);
															exit(0);
														break;
														default: //child c5
															chiledMethod("C5",PID6);
														break;
													}
											break;
											default: //child C4
												chiledMethod("C4",PID4);
											break;
										}
									break;
									default: // child C3
										chiledMethod("C3",PID4);
									break;
								}
							
						break;
						default: //child C2
							chiledMethod("C2",PID3);
						break;
					}

					
				break;
				default: //child C1
					chiledMethod("C1",PID2);
				break;
			}
						

		default	: // Parent P1
			getpid();
			struct msg parentMsg = createMsg(100,"Hello my child Iam Parent P1");
			sendMsg("P1",parentMsg);
			waitpid(PID1,NULL,0);
			reciveMsg("P1");
			printf("P1 terminated\n");
				if (msgctl(MQID, IPC_RMID, NULL) == -1) {
						fprintf(stderr, "Message queue could not be deleted.\n");
						exit(EXIT_FAILURE);
					}
			exit(0);
			
			break;
			
	
	}





	return 0;
}


