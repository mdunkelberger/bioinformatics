#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std::chrono;

void score(int row, int col, int ** array, std::string dna1, std::string dna2);
void print_arr(int rows, int columns, int ** array);
bool checkDiag(int row, int col, int ** array, std::string dna1, std::string dna2);

bool checkVert(int row, int col, int ** array);
bool checkHorizontal(int row, int col, int ** array);
//function to find way back up string
void findAlignment(int row, int col, int ** array, std::string dna1, std::string dna2);

int main() {
  std::ifstream file;
  std::string name;
  std::cout<<"Enter filename: ";
  std::cin>>name;
  //high_resolution_clock::time_point t1 = high_resolution_clock::now();
  
  file.open(name);

  std::string line1;
  std::getline(file, line1);
  std::string line2;
  std::getline(file, line2);
  file.close();
  int rows = line1.length()+1 ;
  
  int columns = line2.length()+1 ;

  int **dp_table = new int *[rows];
  for(int i = 0; i < rows; i++){
	  dp_table[i] = new int[columns];
  }
  score(rows, columns, dp_table, line1, line2);

  print_arr(rows, columns, dp_table);
  
  findAlignment((rows-1), (columns-1), dp_table, line1, line2);
  

  
  //high_resolution_clock::time_point t2 = high_resolution_clock::now();
		//auto duration = duration_cast<nanoseconds>( t2 - t1 ).count();
 // std::cout<<duration<<" nanoseconds\n";
}
void score(int row, int col, int ** array, std::string dna1, std::string dna2){
	for(int i = 0; i < row; i++){
		array[i][0] = -2 *i;
	}
	for(int j = 0; j < col; j++){
		array[0][j] = -2 *j;
	}
	for(int i = 1; i < row; i++){
		for(int j = 1; j < col; j++){
			int diag = -1;//mismatch
		
			if(dna1[i-1] == dna2[j-1])
				diag = 2;
		
			if(((array[i-1][j-1]+diag) > (array[i-1][j] -2)) && ((array[i-1][j-1]+diag) > (array[i][j-1] -2))){
				array[i][j] = array[i-1][j-1] +diag;
			}
			else if((array[i-1][j] -2 ) > (array[i][j-1] -2)){
				array[i][j] = array[i-1][j] -2;
			}
			else
				array[i][j] = array[i][j-1] -2;
		}
	}
	
}
void print_arr(int rows, int columns, int **array) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      printf("%4d", array[i][j]);
    }
    std::cout << std::endl;
  }
}
bool checkDiag(int row, int col, int ** array, std::string dna1, std::string dna2){
	//std::cout<<"Row: "<<dna1[row-1]<<" Col: "<<dna2[col-1];
	if( ( (array[row-1][col-1] == (array[row][col] -2) ) && (dna1[row-1] == dna2[col-1] ) ) || (array[row-1][col-1] == (array[row][col] +1) ) ){
		//std::cout<<"Check Diagonal\n";
		return true;
	}
	
	return false;
}
bool checkVert(int row, int col, int ** array){
	if(array[row-1][col] == (array[row][col] + 2)){	
		return true;
	}
	return false;
}
bool checkHorizontal(int row, int col, int ** array){
	if(array[row][col-1] == (array[row][col] + 2)){
		
		return true;
	}
	return false;
}
void findAlignment(int row, int col, int **array, std::string dna1, std::string dna2)	{

	
	std::string align = "";
	
	bool diag; 
	bool vert; 
	bool horz; 

	bool branch = false;
	std::string::iterator it = dna2.end(); --it;
	
	while(row > 0 || col > 0){
	
		diag = checkDiag(row, col, array, dna1, dna2);

		vert = checkVert(row, col, array);

		horz = checkHorizontal(row, col, array);
		
		if((diag && vert)||(diag&&horz)||(vert&&horz))
			branch = true;
		/*
		if(diag && vert && horz){
			findAlignment((row-1), col, array, dna1, dna2, alignment, it, mySet);//horz
			findAlignment(row, (col-1), array, dna1, dna2, alignment, it, mySet);//vert
			row--;
			col--;
			alignment.insert(0, 1, *it);
			--it;
		}
		else if(diag && vert){
			std::string aln2 = alignment;
			aln2.insert(0, "-");
			findAlignment(row, (--col), array, dna1, dna2, aln2, it, mySet);
			row--;
			col--;
			alignment.insert(0, 1, *it);
			--it;
			std::cout<<"hit d/v branch \n";
		}
		else if(diag && horz){
			findAlignment((row-1), col, array, dna1, dna2, alignment, it, mySet);
			row--;
			col--;
			alignment.insert(0, 1, *it);
			--it;
			//dna2.pop_back();
			//std::cout<<"hit d/v branch \n";
		}
		else if(vert && horz){
			findAlignment((row-1), col, array, dna1, dna2, alignment, it, mySet);//branch horizontal
			col--;
			alignment.insert(0, "-");
			//dna2.pop_back();
		}*/
		
		if(diag){
			--row;
			--col;
			align.insert(0, 1, *it);
			--it;
		}
		else if(vert){
			row--;
			align.insert(0, "-");
			//std::cout<<"hit vertical \n";
		}
	
		else if(horz){
			col--;
			align.insert(0, "-");
		}
		else
			break;
	}

	std::cout<<dna1<<"\n";
	std::cout<<align<<"\n";
	if(branch)
		std::cout<<"YES\n";
	else
		std::cout<<"NO\n";
	
}











