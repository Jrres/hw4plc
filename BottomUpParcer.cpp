#include <iostream>
#include <string>
#include <ios>
#include <iomanip>
#include <cstring>

using namespace std;

#define FAILED 0
#define SUCCESS 1

//token codes
#define LETTER 2
#define DIGIT 3
#define UNKNOWN 99

/* Token codes */
#define Float_Lit 9
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MOD_OP 25
#define LEFT_PAREN 26
#define RIGHT_PAREN 27
#define EQUALS_OP 28
#define LT_OP 29
#define LTE_OP 30
#define GT_OP 31
#define GTE_OP 32
#define AND_OP 33
#define OR_OP 34
#define NOT_EQUALS_OP 35
#define IF_CODE 50
#define WHILE_CODE 51
#define BLOCK_CODE 52
class TOKEN{

    public:
    int charClass;
    char lexeme[100];
    char nextChar;
    int lexLen;
    int token;
    int nextToken;
    char lastToken;
    const char *tokenNames[100];
    FILE *in_fp;
    string keyword;
    TOKEN(){
    setTokens();
/* Open the input data file and process its contents */
        if ((in_fp = fopen("front.in", "r")) == NULL){
            printf("ERROR - cannot open front.in \n");
        }
        else {
            getChar();
        }
    }
    void setTokens(){
    tokenNames[LETTER]="LETTER";
    tokenNames[DIGIT ] ="DIGIT";
    tokenNames[UNKNOWN] = "UNKNOWN";
    tokenNames[Float_Lit ] = "FLOATING_POINT_LIT";
    tokenNames[INT_LIT ] = "INT_LIT";
    tokenNames[IDENT] = "IDENT";
    tokenNames[ASSIGN_OP ] = "ASSIGN_OP";
    tokenNames[ADD_OP ] = "ADD_OP";
    tokenNames[SUB_OP ] = "SUB_OP";
    tokenNames[MULT_OP] = "MULT_OP";
    tokenNames[DIV_OP ] = "DIV_OP";
    tokenNames[MOD_OP ] = "MOD_OP";
    tokenNames[LEFT_PAREN ] ="LEFT_PAREN";
    tokenNames[RIGHT_PAREN] ="RIGHT_PAREN";
    tokenNames[EQUALS_OP] ="EQUALS_OP";
    tokenNames[LT_OP ] = "LESS_THAN_OP";
    tokenNames[LTE_OP ]= "LESS_THAN_EQUAL_TO_OP";
    tokenNames[GT_OP]  = "GREATER_THAN_OP";
    tokenNames[GTE_OP] = "GREATER_THAN_EQUAL_TO_OP";
    tokenNames[AND_OP ] = "AND_OP";
    tokenNames[OR_OP] = "OR_OP"; 
    }
    void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
		 	charClass = DIGIT;
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
    }
    int lex(void) {
        lexLen = 0;
        getNonBlank();
        bool isfloat = false;
        switch (charClass) {
            /* Identifiers */

            case LETTER:
                if(nextChar=='i'){
                    addChar();
                    getChar();
                    if(nextChar=='f'){
                        nextToken = IF_CODE;
                    }
                }
                else{
                addChar();
                getChar();
                while (charClass == LETTER || charClass == DIGIT) {
                    addChar();
                    getChar();
                }
                nextToken = IDENT;
                }
                break;
            /* Integer && floating point literals */
            case DIGIT:
                addChar();
                getChar();
           
                while (charClass == DIGIT) {
                
                    addChar();
                    getChar();
                }
                if (nextChar == '.'){
                    addChar();
                    getChar();
                    isfloat = true;
                } 
                while(charClass == DIGIT){
                    addChar();
                    getChar();
                }
                if(!isfloat)
                    nextToken = INT_LIT;
                else
                    nextToken=Float_Lit;
                break;
            /* Parentheses and operators */
            case UNKNOWN:
                lookup(nextChar);
                break;
                /* EOF */
            case EOF:
                nextToken = EOF;
                lexeme[0] = 'E';
                lexeme[1] = 'O';
                lexeme[2] = 'F';
                lexeme[3] = '\0';
                break;
        } /* End of switch */
        return nextToken;
    } /* End of function lex */  
    int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 getChar();
			 nextToken = LEFT_PAREN;
			 break;
		 case ')':
			 addChar();
			 getChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 getChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 getChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 getChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 getChar();
			 nextToken = DIV_OP;
			 break;
		 case '%':
		 	addChar();
			getChar();
			nextToken = MOD_OP;
			break;
		 case '=':
		 	addChar();
			getChar();
			getNonBlank();
			nextToken= ASSIGN_OP;
			if(nextChar=='='){
			addChar();
			nextToken = EQUALS_OP;
			getChar();
			}
			break;
		 case '<':
		 	addChar();
			getChar();
			getNonBlank();
			nextToken=LT_OP;
			if(nextChar=='='){
			addChar();
			nextToken=LTE_OP;
			getChar();
			}
		 	break;
		 case '>':
		 	addChar();
			getChar();
			getNonBlank();
			nextToken = GT_OP;
			if(nextChar=='='){
			addChar();
			nextToken=GTE_OP;
			getChar();
			}
			
		 	break;
		 case '&':
		 	addChar();
			getChar();
			getNonBlank();
			nextToken=AND_OP;
			if(nextChar=='&'){
			addChar();
			nextToken=AND_OP;
			getChar();
			}
			
		 	break;
		 case '|':
		 	addChar();
			getChar();
			getNonBlank();
			nextToken=OR_OP;
			if(nextChar=='|'){
			addChar();
			nextToken=OR_OP;
			getChar();
			}
		 	break;
		 default:
			 addChar();
			 getChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
} 
};  

class BOOL_EXPR{
    /*
    15 points |<BOOL_EXPR> --> <BTERM> {(`>`|`<`|`>=`|`<=`) <BTERM>}

    <BTERM> --> <BAND> {(`==`|`!=`) <BAND>}
    <BAND> --> <BOR> {`&&` <BOR>}
    <BOR> --> <EXPR> {`&&` <EXPR>}
    */
    public:
    char ptr;
    TOKEN v1;
    BOOL_EXPR(TOKEN v){
        v1 = v;
        ptr = v1.nextChar;
        cout <<" ------enter the if grammar---------: \n";
        if(BEXP() && v1.nextChar == ')'){
                cout << "this boolean expression is successfully parsed\n";
            }
        else 
            cout << "parsing error\n";
    }
    BOOL_EXPR(){
        ptr = v1.nextChar;
        cout << "Parser for logical expressions\n";
        cout << "Step" << setw(25) << "" << "Input\n" ;
        cout << "------------------------------------\n";
        if(BEXP() && v1.nextChar == EOF){
            cout << "this boolean expression is successfully parsed\n";
        }
        else 
            cout << "parsing error\n";
    }
    bool isVALID(){
        if(BEXP() && v1.nextChar == ')'){
                return SUCCESS;
        }
        else 
            return FAILED;
    }
    bool isid(){
        char curr = ptr;
        if(!isalpha(curr))
        return 0;
        while(isdigit(curr) || isalpha(curr)){
            v1.getChar();
            ptr = v1.nextChar;
        }
        return true;
    }
    void removeWhiteSpace(){
        while(ptr==' '){
            ptr++;
        }
        return;
    }
    bool BINQ(){
        if(ptr == '<' || ptr == '>'){
            if(ptr == '<'){
                v1.lex();
                v1.getNonBlank();
                ptr = v1.nextChar;
                v1.getNonBlank();
                if(v1.nextToken == LTE_OP){
                    cout<<"BEXP -> <= BTERM BEXP"<<setw(8)<<""<<"<="<< "\n";
                }
                else
                cout<<"BEXP -> < BTERM BEXP"<<setw(8)<<""<<ptr<< "\n";
         
            }
            else{
                v1.lex();
                v1.getNonBlank();
                ptr = v1.nextChar;
                v1.getNonBlank();
                if(v1.nextToken == GTE_OP){
                    cout<<"BEXP -> >= BTERM BEXP"<<setw(8)<<""<<">="<< "\n";

                }
                else
                cout<<"BEXP -> > BTERM BEXP"<<setw(8)<<""<<ptr<< "\n"; 
               
            }
            if(BTERM()){
                v1.getNonBlank();
                if(BINQ()){
                    return SUCCESS;
                }
                else{ 
                    return FAILED;
                }
            }
            else{
                return FAILED;
            }
        }
        else{
            cout<<"BEXP -> $"<< std::setw(17) << ""<< ptr << "\n";
            return SUCCESS;
        }
    }
     bool BEXP(){
        v1.getNonBlank();
        cout <<"BEXP -> BTERM BEXP'" << setw(10) << "" <<ptr<< "\n";
        if(BTERM()){
            if(BINQ()){
                return SUCCESS;
            }
            else{
                return FAILED;
            }
        }
        else return FAILED;
    }
    bool BEQ(){
        v1.getNonBlank();
        if(ptr == '='){
            v1.lex();
            v1.getNonBlank();
            ptr = v1.nextChar;
            v1.getNonBlank();
            if(v1.nextToken==EQUALS_OP){
                cout << "BAND -> == BAND BTERM" <<setw(8)<<""<< "==" <<"\n";

                if(BAND()){
                    if(BEQ()){
                        return SUCCESS;
                    } 
                    else{
                        return FAILED;
                    }
                    return SUCCESS;
                }
                else return FAILED;
            }
            else{
                return FAILED;
            }
        }
        else if(ptr =='!'){
            v1.getNonBlank();
            v1.lex();
            v1.getNonBlank();
            ptr = v1.nextChar;
            if(v1.nextToken==NOT_EQUALS_OP){
                cout << "BAND -> != BAND BTERM" <<setw(8)<<""<< "!=" <<"\n";
                if(BOR()){
                    v1.getNonBlank();
                    if(BEQ()){
                        return SUCCESS;
                    }
                    else {
                    return FAILED;
                    }                
                }
                else{
                    return FAILED;
                }
            }
            else{
                return FAILED;
            }
        }
        else{
            cout << "BAND -> $" <<setw(20)<<""<< ptr <<"\n";
            return SUCCESS;
        }
    }
    bool BTERM(){
        v1.getNonBlank();
        cout <<"BTERM -> BAND BTERM'" << setw(9) << "" <<ptr<< "\n";
        if(BAND()){
            if(BEQ()){
                return SUCCESS;
            }
            else{
                return FAILED;
            }
        }
        else{
            return FAILED;
        }
    }
    bool BINC(){
        v1.getNonBlank();
        if(ptr == '&'){
            v1.getNonBlank();
            v1.lex();
            v1.getNonBlank();
            ptr = v1.nextChar;
            if(v1.nextToken==AND_OP){
                cout << "BOR -> && BOR BAND "<< setw(10)<<""<<"&&"<<"\n";

                if(BOR()){
                    v1.getNonBlank();
                    if(BINC()){
                        return SUCCESS;
                    }
                    else{
                        return FAILED;
                    }
                }
                else{
                    return FAILED;
                }
            }else 
            return FAILED;
        }
        else{
            cout << "BOR -> $"<< setw(21)<<""<<ptr<<"\n";
            return SUCCESS;
        }
    }
    bool BAND(){
        v1.getNonBlank();
        cout << "BAND -> BOR BAND'" << setw(12) << ""<<ptr << "\n";
        if(BOR()){
            if(BINC()){
                return SUCCESS;
            }
            else
                return FAILED;
        }
        else
            return FAILED;
    }
    bool BOR(){
        v1.getNonBlank();
        if(ptr == '&'){
            if(BINC()){
                if(BEXP()){
                    return SUCCESS;
                }
                else{
                    return FAILED;
                }
            }
            else 
            {
                return FAILED;
            }
        }
        else if(isdigit(ptr) || isid()){
            cout << "BOR -> val"<< setw(19)<<""<<ptr<<"\n";
            v1.lex();
            v1.getNonBlank();
            ptr= v1.nextChar;
            return SUCCESS;
        }
        else{
            return FAILED;
        }
    }
};
class EXPR{
    /*
    Recursive descent parser 
    E –> T E’ 
    E’ –> + T E’ | e 
    T –> F T’ 
    T’ –> * F T’ | e 
    F –> ( E ) | id
    */
    public:
        char ptr;
        TOKEN v1;
        EXPR(){
           //start Symbol
            cout << "Parser for arithmetic expressions\n";
            cout << "Step" << setw(11) << "" << "Input\n" ;
            cout << "-------------------------\n";
            ptr = v1.nextChar;        
            if(E() && v1.nextChar == EOF){
                cout<<"expression is parsed\n";
            }else{
                cout<<"parsing error\n";
            }

        }
        EXPR(TOKEN v){
           //start Symbol
            v1=v;
            cout << "Parser for arithmetic expressions\n";
            cout << "Step" << setw(11) << "" << "Input\n" ;
            cout << "-------------------------\n";
            ptr = v1.nextChar;        
            if(E() && v1.nextChar == '}'){
                cout<<"string is parsed\n";
            }else{
                cout<<"parsing error\n";
            }

        }

        bool EXP(){
            v1.getNonBlank();
            if(ptr == '+' || ptr == '-' ){
                v1.getNonBlank();
                if(ptr == '+')
                cout << "E' -> +TE"<< std::setw(6) << "" <<ptr << "\n";
                else 
                cout << "E' -> -TE"<< std::setw(6) << ""<<ptr << "\n";
                v1.lex();
                v1.getNonBlank();
                ptr=v1.nextChar;
                if(T()){
                    if(EXP()){
                        return SUCCESS;
                    }
                    else{
                        return FAILED;
                    }
                }
                else{
                    return FAILED;
                }
            }
            else{
                cout << "E' -> $"<< std::setw(8) << ""<<ptr << "\n";
                return SUCCESS;
            }
        }
        bool E(){
            v1.getNonBlank();
            cout << "E -> T E'" << std::setw(6) << ""<< ptr << "\n";
            if(T()){
                if(EXP()){
                    return SUCCESS;
                }
                else{
                    return FAILED;
                }
            }
            else{
               return FAILED;
            }
        }
        bool TERM(){
            v1.getNonBlank();
            
            if(ptr == '*'|| ptr == '/' || ptr == '%'){
                if(ptr == '*')
                cout<< "T -> *F T'"<< std::setw(5) << "" << ptr << "\n";
                else if(ptr == '/')
                cout<< "T -> /F T'" << std::setw(5) << ""<< ptr << "\n";
                else
                cout<< "T -> %F T'"<< std::setw(5) << "" << ptr << "\n";
                v1.lex();
                v1.getNonBlank();
                ptr=v1.nextChar;
                if(F()){
                    v1.getNonBlank();
                    if(TERM()){
                        return SUCCESS;
                    }
                    else{
                        return FAILED;
                    }
                }
                else{
                    return FAILED;
                }
            }
            else{
                cout << "T' -> $" << std::setw(8) << ""<< ptr << "\n";
                return SUCCESS;
            }
        }
        bool T(){
            v1.getNonBlank();
            cout << "T -> F T'"<< std::setw(6) << ""<<ptr<<"\n";
            
            if(F()){
                v1.getNonBlank();
                
                if(TERM()){
                    
                    return SUCCESS;
                }
                else{
                    return FAILED;
                }
            }
            else{
                return FAILED;
            }
        }
        bool isid(){
            char curr = ptr;
            if(!isalpha(curr))
            return 0;
            v1.lex();
            v1.getNonBlank();
            ptr=v1.nextChar;
            return true;
        }
        bool F(){
            v1.getNonBlank();
            if(ptr == '('){
                cout<<"F -> ( E )"<< std::setw(5) << ""<< ptr << "\n";
                v1.lex();
                v1.getNonBlank();
                ptr=v1.nextChar;
                if(E()){
                    if(ptr ==')'){
                        v1.lex();
                        v1.getNonBlank();
                        ptr=v1.nextChar;

                        return SUCCESS;
                    }
                    else{
                        return FAILED;
                    }
                }
                else{
                    return FAILED;
                }
            }
            else if(isdigit(ptr) || isid()){
                cout<<"F -> val"<< std::setw(7) << ""<< ptr << "\n";
                v1.lex();
                v1.getNonBlank();
                ptr=v1.nextChar;
                return SUCCESS;
            }
            else{
                return FAILED;
            }
        }
};
class STMT{
    //<BLOCK> --> `{` <STMT_LIST> `}`
    char ptr;
    TOKEN v1;
    public:
    STMT(){
        cout << "Parser for single Statements\n";
        cout << "Step" << setw(25) << "" << "Input\n" ;
        cout << "------------------------------------\n";
        ptr = v1.nextChar;
        if(STMT_TYPE() && v1.nextToken==EOF){
            cout << "Statement was successfully parsed\n";
        }
        else{
            cout << "Parsing error\n";
        }
    }
    bool IFSTMT(){
        cout << " <STMT> --> if <IF_STMT>" << setw(8) << "" << "if(" <<"\n";
        v1.getChar();
        v1.getNonBlank();
        ptr = v1.nextChar;
        if(ptr == '('){
            v1.getChar();
            v1.getNonBlank();
            BOOL_EXPR b1(v1);
            v1 = b1.v1;
            return SUCCESS;
        }
        else{
            return FAILED;
        }

    }
    bool WHILESTMT(){
        cout << "TEST";
        
       return SUCCESS;
    }
    bool EXP(){
     cout << " <STMT> -->  EXP <EXPR>" << setw(8) << "" <<"\n";
        EXPR e1(v1);
        v1 = e1.v1;
        return SUCCESS;
    }
    bool BLOCK(){
    
        if(ptr == '{'){
            cout << "BLOCK - > '{'" << setw(16) << "" << ptr <<"\n";
           v1.getNonBlank();
           v1.getChar();
           if(!isdigit(v1.nextChar))
           v1.lex();
            //sets token to if code
           ptr = v1.nextChar;
           //might need to check if theres an expression here 
           if(STMT_TYPE()){

            ptr = v1.nextChar;
            cout << ptr;
                if(ptr == '}'){
                    
                    cout << "BLOCK - > '{END_BLOCK}'" << setw(8) << "" << ptr <<"\n";
                    v1.lex();
                    return SUCCESS;
                }
                else{
                    return FAILED;
                }
           }
           else{
            return FAILED;
           }

        }
        else {
            return FAILED;
        }
    }
    bool STMT_TYPE(){
        if(BLOCK()){
            return SUCCESS;
        }
        else if(v1.nextToken==IF_CODE){
            if(IFSTMT()){
                return SUCCESS;
            }
            else{
                return FAILED;
            }
        }
        else if(v1.nextToken==WHILE_CODE){
            if(WHILESTMT()){
                return SUCCESS;
            }
            else{
                return FAILED;
            }
        }
        else if(EXP()){
            return SUCCESS;
        }
        else{
            return FAILED;
        }
    }

};
/*
function to initalize parsers for expressions bool expression and statements. 

for test cases 
expressions: you can try any algebraic expression like 1+2*3/2
bool_exprs: you can use &&, <=, >=, etc in a statement like 1 <= 2 == 3 && 2
statements: you can start with a block {if(1<2)}, {1==2}

*/
int main() {
    cout << std::left;
    EXPR s1;
    BOOL_EXPR b1;
    STMT c1;
    return 0;
}
