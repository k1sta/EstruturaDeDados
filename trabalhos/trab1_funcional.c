#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	struct node* next;
	int x;
	char c;
} tNode;

typedef struct stack{
	tNode* top;
} tStack;


int stckInitializer (tStack* ptr); //initializes the stack

int pushNumStck (tStack* ptr, int x); //pushes a number into a node into the stack

int pushCharStck (tStack* ptr, char c);

int popNumStck (tStack* ptr); //pops a number out of a stack (and deletes it)

char popCharStck (tStack* ptr);

void freeStck (tStack* ptr); //frees an empty stack
			     
void printStcks (tStack* numStckPtr, tStack* opStckPtr);

int operate(tStack* numStckPtr, tStack* opStckPtr);

int main (void) {
	tStack* numStckPtr;
	tStack* opStckPtr;
	char* buffer;	
	
	//initializing stuff
	numStckPtr = (tStack*) malloc (sizeof(tStack));
	if (numStckPtr == NULL){
		puts("Error alocating memory");
		exit(1);
	}
	stckInitializer(numStckPtr);
	opStckPtr = (tStack*) malloc (sizeof(tStack));
	if (opStckPtr == NULL){
		puts("Error alocating memory");
		exit(1);
	}
	stckInitializer(opStckPtr);
	buffer = (char*) malloc (100);
	if (buffer == NULL){
		puts("Error alocating memory");
		exit(1);
	}


	//input
	printf("%s", "insert the equation: \n");
	fgets(buffer, 100, stdin); //using fgets cause i dont wanna a bof fail right now

	for(int i = 0; i < 100 || buffer[i] == '\n' || buffer[i] == '\0'; i++){
		char charAtual = buffer[i];
		if(buffer[i] >= '0' && buffer[i] <= '9'){
			int x, n;
			char c;

			sscanf(buffer + i, "%d %c%n", &x, &c, &n);
			
			pushNumStck(numStckPtr, x);

			if(c == ')'){
				operate(numStckPtr, opStckPtr);
			} else{
				pushCharStck(opStckPtr, c);
			}

			i += n - 1;
			//printStcks(numStckPtr, opStckPtr);


		} else if (buffer[i] == '+' || buffer[i] == '-' || buffer[i] == '*' || buffer[i] == '/'){
			pushCharStck(opStckPtr, charAtual);
			//printStcks(numStckPtr, opStckPtr);

		} else if (buffer[i] == ')'){
			operate(numStckPtr, opStckPtr);
			//printStcks(numStckPtr, opStckPtr);
		}

	}

	printf("Answer: %d\n", popNumStck(numStckPtr));


	free(buffer);
	freeStck(numStckPtr);
	freeStck(opStckPtr);

	return 0;
}

int stckInitializer (tStack* ptr){ //initializes the stack
	ptr->top == NULL;

	return 0;
}

int pushNumStck (tStack* ptr, int x){ //pushes a number into a node into the stack
	tNode* node = (tNode*) malloc (sizeof(tNode));
	if (node == NULL){
		exit (1);
	}
	
	node->x = x;
	node->next = ptr->top;
	ptr->top = node;
	
	return 0;
}

int pushCharStck (tStack* ptr, char c){ //pushes a number into a node into the stack
	tNode* node = (tNode*) malloc (sizeof(tNode));
	if (node == NULL){
		exit (1);
	}
	
	node->c = c;
	node->next = ptr->top;
	ptr->top = node;
	
	return 0;
}

int popNumStck (tStack* ptr){ //pops a number out of a stack (and deletes it)
	tNode* deletion = ptr->top;
	int x = deletion->x;
	
	ptr->top = deletion->next;
	
	free(deletion);

	return x;
}

char popCharStck (tStack* ptr){ //pops a number out of a stack (and deletes it)
	tNode* deletion = ptr->top;
	char c = deletion->c;
	
	ptr->top = deletion->next;
	
	free(deletion);

	return c;
}

void freeStck (tStack* ptr){ //frees a stack
	while(ptr->top != NULL){
		popNumStck(ptr);
	}

	free(ptr);
}


int operate(tStack* numStckPtr, tStack* opStckPtr){
	char op = popCharStck(opStckPtr);
	int n1 = popNumStck(numStckPtr), n2 = popNumStck(numStckPtr);

	switch (op){
		case '+':
		pushNumStck(numStckPtr, n2 + n1);
		break;

		case '-':
		pushNumStck(numStckPtr, n2 - n1);
		break;

		case '*':
		pushNumStck(numStckPtr, n2 * n1);
		break;

		case '/':
		pushNumStck(numStckPtr, n2 / n1);
		break;

		default:
	}

	return 0;
}

void printStcks (tStack* numStckPtr, tStack* opStckPtr){
	tNode* numPtr = numStckPtr->top;
	tNode* opPtr = opStckPtr->top;

	char* ops = (char*) calloc(50, sizeof(char));
	if(ops == NULL){
	    exit(1);
	}
	
	int* nums = (int *)calloc(50, sizeof(int));
	if(nums == NULL){
	    exit(1);
	}
	
	int i = 0, t = 0;

	while(opPtr != NULL){
		ops[i] = opPtr->c;
		opPtr = opPtr->next;
		i++;
	}

	i = 0;

	while(numPtr != NULL){
		nums[i] = numPtr->x;
		numPtr = numPtr->next;
		i++;
	}
    
    puts("Iteração:");
    i--;
	while(i >= 0){
		printf("%d | %c\n", nums[t], ops[t]);
		i--;
		t++;
	}
	
	if(numStckPtr->top != NULL && opStckPtr->top != NULL) printf("Ultimo PushNum: %d\nUltimo PushChar: %c\n", numStckPtr->top->x, opStckPtr->top->c);
	
	puts("");
}

