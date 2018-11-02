#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <chrono>
using namespace std::chrono;
void score(int rows, int columns, int array[], std::string dna1, std::string dna2);
void print_arr(int rows, int columns, int array[]);
bool checkDiag(int loc, int row, int array[]);
bool checkVert(int loc, int row, int array[]);
bool checkHorizontal(int loc, int row, int array[]);
//function to find way back up string
void findAlignment(int loc, int row, int array[], std::string dna1, std::string dna2, std::string alignment);

int main() {
  std::ifstream file;
  std::string name;
  std::cout<<"Enter filename: ";
  std::cin>>name;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  
  file.open(name);

  std::string line1;
  std::getline(file, line1);
  std::string line2;
  std::getline(file, line2);
  file.close();
  int rows = line1.length()+1 ;
  
  int columns = line2.length()+1 ;
	//std::cout<<rows<<" "<<columns<<"\n";
  int dp_table[rows*columns];

  score(rows, columns, dp_table, line1, line2);

  print_arr(rows, columns, dp_table);

  int loc = ((rows*columns) -1);
  std::set<std::string> alignments;
  std::string str = "";
  findAlignment(loc, rows, dp_table, line1, line2, str);
  
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>( t2 - t1 ).count();
  std::cout<<duration<<" nanoseconds\n";
}

void  score(int rows, int columns, int array[], std::string dna1, std::string dna2) {

  //initialize values of first row and column
  for (int i = 0; i < rows; ++i) {
    array[i*columns] = i * -2;
  }
  for (int j = 1; j < columns; ++j) {
    array[j] = j* -2;
  }

  //dp algorithm
  for (int i = 1; i < rows; ++i) {
    for (int j = 1; j < columns; ++j) {
      //determine if characters are a match
      int diag = -1;
      if (dna1[i - 1] == dna2[j - 1]) {
        diag = 2;
      }

      //determine whether to take vertical, horizontal, or diagonal value
      if (((array[(i - 1)*columns + j - 1] + diag) > (array[(i-1)*columns + j] - 2)) && ((array[(i - 1)*columns + j - 1] + diag) > (array[i*columns + j-1] - 2))) {
        array[i*columns + j] = array[(i - 1)*columns + j - 1] + diag;
      }
      else if (array[(i - 1)*columns + j] - 2 > array[i*columns + j - 1] - 2) {
        array[i*columns + j] = array[(i - 1)*columns + j] - 2;
      }
      else {
        array[i*columns + j] = array[i*columns + j - 1] - 2;
      }
    }
  }
}

void print_arr(int rows, int columns, int array[]) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      printf("%4d", array[i*columns + j]);
    }
    std::cout << std::endl;
  }
}
bool checkDiag(int loc, int row, int array[]){
	if((array[loc - (row-1)] == (array[loc] -2)) || ( array[loc -row+1] == (array[loc] +1))){
		return true;
	}
	return false;
}
bool checkVert(int loc, int row, int array[]){
	if(array[loc -(row-2)] == (array[loc] + 2)){
		return true;
	}
	return false;
}
bool checkHorizontal(int loc, int row, int array[]){
	if(array[loc - 1] == (array[loc] + 2)){
		return true;
	}
	return false;
}
void findAlignment(int loc, int row, int array[], std::string dna1, std::string dna2, std::string alignment)	{
	//columns matches to dna2 (sequence to be aligned to first
	
	int index = loc;
	//std::cout<<loc<<"\n";
	bool diag;
	bool vert;
	bool horz;
	bool branch = false;
	std::string::iterator it = dna2.end(); --it;
	while(index > 0){
		//check diagonal for match/mismatch
		diag = checkDiag(loc, row, array);
		vert = checkVert(loc, row, array);
		horz = checkHorizontal(loc, row, array);
		//std::cout<<diag<<" "<<vert<<" "<<horz<<"\n";
		/*
		if(diag){
			loc -= (row + 1);
			alignment.insert(0, 1, dna2.back());
			dna2.pop_back();
		}
		else if(vert){
			loc -= row;
			alignment.insert(0, "-");
			dna2.pop_back();
		}
		else if(horz){
			
		}
		if(diag&&vert)
			branch = true;
		index--;
		*/
		if(vert){
			loc = (loc - (row-2));
			alignment.insert(0, "-");
			//dna2.pop_back();
			//std::cout<<"hit vertical \n";
		}
		else if(diag){
			loc = (loc - row+1);
			alignment.insert(0, 1, *it);
			--it;
			//std::cout<<"hit diag"<<"\n";
		}
		
		else if(horz){
			loc = (loc - 1);
			alignment.insert(0, "-");
			//dna2.pop_back();
			//std::cout<<"hit horizontal \n";
		}
		else
			break;
		if((diag && vert)||(diag&&horz)||(vert&&horz))
			branch = true;
		/*
		if(diag && vert && horz){
			findAlignment((loc-(row-2)), row, array, dna1, dna2, alignment);
			findAlignment((loc-1), row, array, dna1, dna2, alignment);
			loc = (loc - row+1);
			alignment.front() = dna2.back();
			dna2.pop_back();
		}
		else if(diag && vert){
			findAlignment((loc-(row-2)), row, array, dna1, dna2, alignment.substr(0));
			loc = (loc - row+1);
			alignment.insert(0, 1, *it);
			//dna2.pop_back();
			--it;
			std::cout<<"hit d/v branch \n";
		}
		else if(diag && horz){
			findAlignment((loc-1), row, array, dna1, dna2, alignment);
			loc = (loc - row+1);
			alignment.insert(0, 1, dna2.back());
			dna2.pop_back();
			std::cout<<"hit d/v branch \n";
		}
		else if(vert && horz){
			findAlignment((loc -1), row, array, dna1, dna2, alignment);//branch horizontal
			loc = (loc - (row+2));
			alignment.insert(0, "-");
			dna2.pop_back();
		}
		*/
		//else if(!diag && !vert && !horz)
		//	break;
		index--;
	}
	if(loc > 0)
		return;
	//mySet.insert(alignment);
	std::cout<<dna1<<"\n";
	std::cout<<alignment<<"\n";
	if(branch)
		std::cout<<"YES\n";
	else
		std::cout<<"NO\n";
	
	
}











