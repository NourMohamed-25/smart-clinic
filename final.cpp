#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Patient {
    string name;
    int age ;
    string symptoms;
    string start_time;
    string end_time ;
    int urgency_score ; } ;

int calculate_urgency(int age,string symptoms) {
     int score =0;
    if (age <=5 || age >=65){
        score+=20;
    }
    int pos = symptoms.find("chest pain");
    if(pos != -1){
        score+=20 ;
    }
    int pos2 = symptoms.find ("shortness of breath");
    if ( pos2 != -1){
        score+=30;
    }
    int pos3 = symptoms.find("loss of consciousness");
    if ( pos3 != -1){
        score+=40 ;
    }
    int pos4 = symptoms.find("sudden weakness");
    if(pos4 != -1){
        score+=50 ;
    }
    int pos5 =symptoms.find("high fever");
    if( pos5 != -1){
        score+=60 ;
    }
    int pos6 =symptoms.find("skin rash");
    if (pos6 != -1){
        score+= 70;
    }
    if (score == 0){
        score =5 ;
    }
    return score ;
}
void selection_sort(Patient patients[],int size){
    for( int i =0 ;i< size-1 ; i++){
        int max = i;
        for(int j =i+1 ;j <size ;j++){
            if(patients[j].urgency_score > patients[max].urgency_score){
                max = j ;
              }
        }
        swap(patients[i], patients[max]);
    }
}
int main () {
    ifstream infile("patients.txt");
    if (!infile.is_open()){
        cout<<"Error: Could not open patients.txt"<<endl;
        return 1;
    }
    Patient patients[5];
    int count = 0 ;
    while(infile >> patients[count].name >> patients [count].age ){
        infile.ignore();
        getline(infile,patients[count].symptoms);
        infile >> patients[count].start_time >> patients[count].end_time;
        patients[count].urgency_score = calculate_urgency(patients[count].age,patients[count].symptoms);
        count++;
    }
    infile.close();
    selection_sort(patients,count);
    ofstream outfile("result.txt");
  if (!outfile.is_open()) {
    cout << "Error: Could not create result.txt" << endl;
    return 1;
}

for(int i = 0; i < count; i++){
        outfile<< patients[i].name<<","<<patients[i].urgency_score << endl;

    } outfile.close();
    cout<< "Process completed successfully";

 
 return 0 ;
}
