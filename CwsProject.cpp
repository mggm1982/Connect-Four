#include<iostream>
#include <vector>
#include <string>

using namespace std;
const string RED = "\033[1;31m";    
const string YELLOW = "\033[1;33m"; 
const string BLUE = "\033[1;34m";   
const string RESET = "\033[0m";     

const int R=6,C=7;
const char EMPTY='.', P1='X', P2='O';
char b[R][C];
void printBoard();
int drop(int col, char p);
bool win(int r, int c, char p);
bool draw();
bool trymove(int col,char p);
int aimove();

int main(){
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            b[i][j]=EMPTY;

    cout<<"Connect Four\n1) Two Players\n2) Vs Computer\nChoice: ";
    int mode; cin>>mode;
    char p=P1;
    while(true){
        printBoard();
        int c=-1;
        if(p==P1 || mode==1){
            string player_color = (p == P1) ? RED : YELLOW;
            cout<<"Player "<<(p==P1? 1:2);
             cout<<" [" << player_color << p << RESET ;
             cout<<"] choose column (1-7): ";
            cin>>c;c--;
        }
        else{
            c = aimove();
            cout<<"Computer chooses column "<<c+1<<endl;
        }
        int r=drop(c,p);
        if(r==-1){ cout<<"Invalid move, try again.\n"; continue; }
        if(win(r,c,p)){
            printBoard();
            string winner_color = (p == P1) ? RED : YELLOW;
            string winner_message;
            if (p == P1) {
                winner_message = "Player 1";
            } else {
                if (mode == 2) {
                    winner_message = "Computer";
                } else {
                    winner_message = "Player 2";
                }
            }
            cout << winner_color << winner_message << " WINS!\n" << RESET;
            break;
        }
        if(draw()){
            printBoard();
            cout<<"It's a DRAW!\n";
            break;
        }
        p=(p==P1?P2:P1);
    }
    return 0;
}

void printBoard(){
    cout<<"\n";
    for(int i=0;i<R;i++){
        cout<<BLUE<<"| "<<RESET;
        for(int j=0;j<C;j++){
            if (b[i][j] == P1) {
                cout << RED << b[i][j] << RESET << " ";
            } else if (b[i][j] == P2) {
                cout << YELLOW << b[i][j] << RESET << " ";
            } else {
                cout<<b[i][j]<<" ";
            }
        }
        cout<<BLUE<<"|\n"<<RESET;
    }
    cout<<BLUE<<"+";
    for(int j=0;j<C*2+1;j++) cout<<"-";
    cout<<"+\n"<<RESET<<"  ";
    for(int j=0;j<C;j++) cout<<j+1<<" ";
    cout<<"\n\n";
}
int aimove(){
    for(int c=0;c<C;c++){
        if(b[0][c]==EMPTY && trymove(c,P2)) return c;
    }
    for(int c=0;c<C;c++){
        if(b[0][c]==EMPTY && trymove(c,P1)) return c;
    }
    vector<int> pref={3,2,4,1,5,0,6};
    for(int c:pref) if(b[0][c]==EMPTY) return c;
    return 0; 
}
bool win(int r ,int c , char p){
   int count;
   count =1;
   for(int j = c-1; j>=0 && b[r][j]==p ; j--){
   count++;
   }
    for(int j = c+1; j < C && b[r][j] == p; j++) count++;
    if(count >= 4) return true;
    count = 1;
    for(int i = r-1; i >= 0 && b[i][c] == p; i--) count++;
    for(int i = r+1; i < R && b[i][c] == p; i++) count++;
    if(count >= 4) return true;
    count = 1;
    for(int i=r-1, j=c-1; i>=0 && j>=0 && b[i][j]==p; i--, j--) count++;
    for(int i=r+1, j=c+1; i<R && j<C && b[i][j]==p; i++, j++) count++;
    if(count >= 4) return true;
    count = 1;
    for(int i=r-1, j=c+1; i>=0 && j<C && b[i][j]==p; i--, j++) count++;
    for(int i=r+1, j=c-1; i<R && j>=0 && b[i][j]==p; i++, j--) count++;
    if(count >= 4) return true;
    return false;
}

bool trymove(int col,char p){
    for(int i=R-1;i>=0;i--) if(b[i][col]==EMPTY){
        b[i][col]=p;
        bool ok=win(i,col,p);
        b[i][col]=EMPTY; 
        return ok;
    }
    return false;
}

int drop(int col,char p){
    if(col<0||col>=C||b[0][col]!=EMPTY) return -1;
    for(int i=R-1;i>=0;i--) if(b[i][col]==EMPTY){ b[i][col]=p; return i; }
    return -1; 
}

bool draw(){
    for(int j=0;j<C;j++)
        if(b[0][j]==EMPTY) return false;
    return true;
}