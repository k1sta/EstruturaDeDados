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
//pop 2 numeros e pop operador
//checar a operacao e realizar com ambos os numeros
//push no resultado

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

	for(int i = 0; i < 100 || buffer[i] == '\n'; i++){
		char charAtual = buffer[i];
		//O QUE ESSE CONDICINAL DEVE FAZER
		//checar se eh um numero
		//checar se eh o final da string
		//checar se eh um operador?
		//checar se eh um parenteses fechado
		if(buffer[i] >= '0' && buffer[i] <= '9'){
			//le 1 numero e 1 operador
			//push na pilha de numeros
			//conferir se operador é ')'
			//se for, realizar 2 pop's de numeros
			//1 pop de operador
			//realizar a operação correspondente com os numeros
			//push no resultado 
			//pegar o proximo operador?
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

		} else if (buffer[i] == '+' || buffer[i] == '-' || buffer[i] == '*' || buffer[i] == '/'){
			pushCharStck(numStckPtr,buffer[i]);
		} else if (buffer[i] == ')'){
			operate(numStckPtr, opStckPtr);
		} else if (buffer[i] == '\0'){
			while(opStckPtr->top != NULL){
				operate(numStckPtr, opStckPtr);
			}
		}

		printStcks(numStckPtr, opStckPtr);
	}

	printf("Answer: %d", popNumStck(numStckPtr));


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

	switch (op){
		case '+':
		pushNumStck(numStckPtr, popNumStck(numStckPtr) + popNumStck(numStckPtr));
		break;

		case '-':
		pushNumStck(numStckPtr, popNumStck(numStckPtr) - popNumStck(numStckPtr));
		break;

		case '*':
		pushNumStck(numStckPtr, popNumStck(numStckPtr) * popNumStck(numStckPtr));
		break;

		case '/':
		pushNumStck(numStckPtr, popNumStck(numStckPtr) / popNumStck(numStckPtr));
		break;

		default:
	}

	return 0;
}

void printStcks (tStack* numStckPtr, tStack* opStckPtr){
	tNode* numPtr = numStckPtr->top;
	tNode* opPtr = opStckPtr->top;

	char ops[50];
	int nums[50];
	int i = 0;

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


	while(i > 0){
		printf("%d %c\n"), nums[i], ops[i-1];
		i--;
	}
	
	printf("%d\n", nums[0]);
}
