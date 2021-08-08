#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<process.h>
#include<ctime>

using namespace std;

class medicine{
public:
char ind[5],drug_ID[5],drug_name[15],manu_date[15],quantity[100],expiry_date[15],MRP[15];
//function declarations
void add_medicine();
int checkID(char *);
void search_medicine();
void delete_medicine();
void display_medicine();
void modify_medicine();
void medicine_module();
int get_num_medicine();
void update_stock();
void retrieve_medicine(char *);

}drugrec[20];
int no1,n1;
int medicine::get_num_medicine()
{
int I=0;
fstream file2;

	
	file2.open("record_medicine.txt",ios::in);
	if(!file2)
	{
		return 0;
	}
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(drugrec[I].ind,5,'|');
		file2.getline(drugrec[I].drug_ID,5,'|');
		file2.getline(drugrec[I].drug_name,15,'|');
		file2.getline(drugrec[I].manu_date,15,'|');
		file2.getline(drugrec[I].expiry_date,15,'|');
		file2.getline(drugrec[I].quantity,100,'|');
		file2.getline(drugrec[I].MRP,15,'\n');
		I++; 	
 	}
	I--;
	file2.close();
	return I;
}
void medicine::retrieve_medicine(char med_no[])
{
	medicine m;

	no1 = m.get_num_medicine();
	for(int i=0;i<no1;i++)
 	{
		if(strcmp(drugrec[i].ind,med_no)==0) 
	 	{
		cout<<"\n\n\n\n";
		cout<<"===============================================================================================================================================\n";
		cout<<"Drug_ID"<<"\t\t"<<"Drug_name"<<"\t\t\t"<<"Manufacture Date"<<"\t\t"<<"Expiry Date"<<"\t\t\t"<<"Quantity"<<"\t\t"<<"MRP"<<"\t"<<endl; 
		cout<<"===============================================================================================================================================\n";
	
		cout<<drugrec[i].drug_ID<<"\t\t"<<drugrec[i].drug_name<<"\t\t\t" <<drugrec[i].manu_date<<"\t\t\t"<<drugrec[i].expiry_date<<"\t\t\t"<<drugrec[i].quantity<<"\t\t\t"<<drugrec[i].MRP<<"\n";
		break;
	 	}
 	}
}


void medicine::add_medicine()
{
char buf1[100],buf2[20];
fstream file1,file2;
int I,cnt;
medicine m;

	cnt=get_num_medicine();

	file1.open("index_medicine.txt",ios::out|ios::app);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	file2.open("record_medicine.txt",ios::out|ios::app);
	if(!file2)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	cout<<"\nEnter the no. of Medicines : ";
	cin>>no1;
	cout<<"\nEnter the details :\n"; 

	for(I=cnt; I<(cnt+no1); I++)
   {    
	   while(1)
	   {     
	   	cout<<"\nEnter the Drug ID 							:";
		cin>>m.drug_ID;
		if(checkID(m.drug_ID)==1)
		{
			cout<<"Record with medicine id "<<m.drug_ID<<" is already present";
		}
		else
		{
			break;
		}

	   }     
		cout<<"\nEnter the Drug Name 				:";
		cin>>m.drug_name;
        cout<<"\nEnter the Manufacture Date (dd/mm/yyyy):";
		cin>>m.manu_date;
		cout<<"\nEnter the Expiry Date (dd/mm/yyyy) 	:";
		cin>>m.expiry_date;
		cout<<"\nEnter the medicine quantity				:";
		cin>>m.quantity;
		cout<<"\nEnter the MRP per quantity 				:";
		cin>>m.MRP;

		sprintf(buf2,"%s|%d\n",m.drug_ID,I);
		file1<<buf2;

		sprintf(buf1,"%d|%s|%s|%s|%s|%s|%s\n",I,m.drug_ID,m.drug_name,m.manu_date,m.expiry_date,m.quantity,m.MRP);
		file2<<buf1;
	}
		file1.close();
		file2.close();
}
int medicine::checkID(char ID[])
{
	fstream app;
	medicine m;
	app.open("record_medicine.txt",ios::in);
	while(!app.eof())
	{
		app.getline(m.ind,5,'|');
		app.getline(m.drug_ID,15,'|');
		app.getline(m.drug_name,15,'|');
		app.getline(m.manu_date,15,'|');
		app.getline(m.expiry_date,15,'|');
		app.getline(m.quantity,100,'|');
		app.getline(m.MRP,15,'\n');
	
		if(strcmp(m.drug_ID,ID)==0)
		{
			return 1;
		}
	}
	app.close();
	
}

void medicine::search_medicine()
{
int I,flag1;
char med_no[5],med_id[5],record_id[5];
fstream file1;
medicine m;

	cout<<"\nPlease enter the drug_ID of the medicine";
	cout<<" whose record is to be displayed\n";
	cin>>med_id;
	file1.open("index_medicine.txt",ios::in); 
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag1=0;
	while(!file1.eof())
	{
		file1.getline(record_id,5,'|'); //medicine id
		file1.getline(med_no,5,'\n');    //index num
		if(strcmp(med_id,record_id)==0)
		{
			m.retrieve_medicine(med_no);         
			flag1=1;                  
			break;
		}
	}
	if(!flag1)
	cout<<"\nRecord search failed !!\n"; 
	file1.close();
}

void delete_medicinerecord(char ID[])
{
int I=0;
fstream file1,file2;
medicine m;
	no1 = m.get_num_medicine();	
	int flag=-1;
	for(I=0;I<no1;I++)       //Check for the record's existence
	{
		if(strcmp(drugrec[I].ind,ID)==0)
		{
			flag=I;
			break;
		}	

	}

	if(flag==-1)                //Record not found
	{
		cout<<"\nError !\n";
		return;
	}
	if(flag==(no1-1))            //Delete found last record
	{
		no1--;
		cout<<"\nDeleted !\n";
		
	}
	else
	{
		for(I=flag;I<no1;I++)
		{
			drugrec[I] = drugrec[I+1];
		}
		no1--;
		cout<<"\nDeleted !\n";
	}

	file1.open("index_medicine.txt",ios::out);  
	file2.open("record_medicine.txt",ios::out);  
	for(I=0;I<no1;I++)                   
	{                                   
		file1<<drugrec[I].drug_ID<<"|"<<I<<"\n";
		file2<<I<<"|"<<drugrec[I].drug_ID<<"|"<<drugrec[I].drug_name <<"|"<<drugrec[I].manu_date<<"|"<<drugrec[I].expiry_date<<"|"<<drugrec[I].quantity<<"|"<<drugrec[I].MRP<<"\n";
	}
	file1.close();
	file2.close();
	return;
}

void medicine::delete_medicine()
{
int I,flag;
char med_no[5],med_id[5],record_id[5];
fstream file1;

	cout<<"\nPlease enter the drug_ID of the medicine ";
	cout<<" whose record is to be deleted\n";
	cin>>med_id;
	file1.open("index_medicine.txt",ios::in);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag=0;

	while(!file1.eof())
	{
		file1.getline(record_id,5,'|');      //Search index file and
		file1.getline(med_no,5,'\n');       //call deletion
		//if index found
		if(strcmp(med_id,record_id)==0)
		{
			delete_medicinerecord(med_no); 
			flag=1;
			break;
		}
	}
	if(!flag)
	cout<<"\nDeletion failed !\n"; 
	file1.close();
	
	
}

void medicine::modify_medicine()
{
	fstream in;
	char ID[5];
	int i=0,j;
	medicine m1[100];
	
	in.open("record_medicine.txt",ios::in);
	if(!in)
	{
		cout<<"file cannot be opened \n";
		exit(0);
	}
	cout<<"Enter the medicine ID\n";
	cin>>ID;

	while(!in.eof())
	{
		in.getline(m1[i].ind,5,'|');
		in.getline(m1[i].drug_ID,5,'|');
		in.getline(m1[i].drug_name,15,'|');
		in.getline(m1[i].manu_date,15,'|');
		in.getline(m1[i].expiry_date,15,'|');
		in.getline(m1[i].quantity,100,'|');
		in.getline(m1[i].MRP,15,'\n');
		i++;

	}
	i--;
	for(j=0;j<i;j++)
	{
		if(strcmp(ID,m1[j].drug_ID)==0)
		{
			cout<<"\n Medicine details before printing";
			cout<<"------------------------------------";
			cout<<"\nIndex      	   :"<<m1[j].ind;
			cout<<"\nMedicine ID  	   :"<<m1[j].drug_ID;
			cout<<"\nMedicine Name 	   :"<<m1[j].drug_name;
			cout<<"\nManufacture date  :"<<m1[j].manu_date;
			cout<<"\nExpiry date  	   :"<<m1[j].expiry_date;
			cout<<"\nQuantity		   :"<<m1[j].quantity;
			cout<<"\nMRP		  	   :"<<m1[j].MRP;

			cout<<"\n\n Enter the  medicine modification details";
			cout<<"\n----------------------------------------------\n";
			cout<<"\nMedicine Name 	   :";	cin>>m1[j].drug_name;
			cout<<"\nManufacture date  :";	cin>>m1[j].manu_date;
			cout<<"\nExpiry date  	   :";	cin>>m1[j].expiry_date;
			cout<<"\nQuantity		   :";	cin>>m1[j].quantity;
			cout<<"\nMRP		  	   :";	cin>>m1[j].MRP;
			break;

		}
	}
	if(j==i)
    {
        cout<<"\nThe record with Medicine_ID "<<ID<<" is not present"; 
        return;
    }

	in.close();

	fstream out;
	out.open("record_medicine.txt",ios::out);
	if(!out)
	{
		cout<<"\n unable to open the file in output mode";
		return;
	}
	
	for(j=0;j<i;j++)
	{
		out<<m1[j].ind<<'|'<<m1[j].drug_ID<<'|'<<m1[j].drug_name<<'|'<<m1[j].manu_date<<'|'<<m1[j].expiry_date<<'|'<<m1[j].quantity<<'|'<<m1[j].MRP<<"\n";
	}
	out.close();
	
}

void medicine::update_stock()
{
	fstream in;
	char ID[5];
	int i=0,j;
	medicine m1[100];
	
	in.open("record_medicine.txt",ios::in);
	if(!in)
	{
		cout<<"file cannot be opened \n";
		exit(0);
	}
	cout<<"Enter the medicine ID\n";
	cin>>ID;

	while(!in.eof())
	{
		in.getline(m1[i].ind,5,'|');
		in.getline(m1[i].drug_ID,5,'|');
		in.getline(m1[i].drug_name,15,'|');
		in.getline(m1[i].manu_date,15,'|');
		in.getline(m1[i].expiry_date,15,'|');
		in.getline(m1[i].quantity,100,'|');
		in.getline(m1[i].MRP,15,'\n');
		i++;

	}
	i--;
	for(j=0;j<i;j++)
	{
		if(strcmp(ID,m1[j].drug_ID)==0)
		{
			cout<<"\n Medicine details before printing";
			cout<<"------------------------------------";
			cout<<"\nIndex      	   :"<<m1[j].ind;
			cout<<"\nMedicine ID  	   :"<<m1[j].drug_ID;
			cout<<"\nMedicine Name 	   :"<<m1[j].drug_name;
			cout<<"\nManufacture date  :"<<m1[j].manu_date;
			cout<<"\nExpiry date  	   :"<<m1[j].expiry_date;
			cout<<"\nQuantity		   :"<<m1[j].quantity;
			cout<<"\nMRP		  	   :"<<m1[j].MRP;

			cout<<"\n\n Enter the  medicine Quantity ";
			cout<<"\n----------------------------------------------\n";
			
			cout<<"\nQuantity		   :";	cin>>m1[j].quantity;

			break;

		}
	}
	if(j==i)
    {
        cout<<"\nThe record with Medicine_ID "<<ID<<" is not present"; 
        return;
    }

	in.close();

	fstream out;
	out.open("record_medicine.txt",ios::out);
	if(!out)
	{
		cout<<"\n unable to open the file in output mode";
		return;
	}
	
	for(j=0;j<i;j++)
	{
		out<<m1[j].ind<<'|'<<m1[j].drug_ID<<'|'<<m1[j].drug_name<<'|'<<m1[j].manu_date<<'|'<<m1[j].expiry_date<<'|'<<m1[j].quantity<<'|'<<m1[j].MRP<<"\n";
	}
	out.close();
}

void medicine::display_medicine()
{
fstream file2;
medicine m;
	
	file2.open("record_medicine.txt",ios::in);
	cout<<"\n\n"<<"medicine details : \n";
	cout<<"=============================================================================================================================================================\n";
	cout<<"Index"<<"\t\t"<<"Drug ID"<<"\t\t"<<"Drug Name"<<"\t\t\t"<<"Manufacture Date"<<"\t\t"<<"Expiry Date"<<"\t\t\t"<<"Quantity"<<"\t\t"<<"MRP"<<"\t"<<endl; 
	cout<<"=============================================================================================================================================================\n";
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(m.ind,5,'|');
		file2.getline(m.drug_ID,15,'|');
		file2.getline(m.drug_name,15,'|');
		file2.getline(m.manu_date,15,'|');
		file2.getline(m.expiry_date,15,'|');
		file2.getline(m.quantity,100,'|');
		file2.getline(m.MRP,15,'\n');
		cout<<m.ind<<"\t\t"<<m.drug_ID<<"\t\t"<<m.drug_name<<"\t\t\t"<<m.manu_date<<"\t\t\t"<<m.expiry_date<<"\t\t\t"<<m.quantity<<"\t\t\t"<<m.MRP<<"\n";
 	}
	file2.close();

}


void medicine_module()
{
    medicine m;
	int choice;

	m.display_medicine();
	for(;;)
	{
		cout<<"\n\n\t\t\t\t\t\t\t===============";
		cout<<"\n\t\t\t\t\t\t\tMedicine Module";
		cout<<"\n\t\t\t\t\t\t\t===============";
		cout<<"\n\n";
		cout<<"\t\t\t\t\t\t\t1:Add Medicine\n";
		cout<<"\t\t\t\t\t\t\t2:Search Medicine\n";
		cout<<"\t\t\t\t\t\t\t3:Delete Medicine\n";
		cout<<"\t\t\t\t\t\t\t4:Display Medicine\n";
		cout<<"\t\t\t\t\t\t\t5.Modify Medicine\n";
		cout<<"\t\t\t\t\t\t\t6.Update Medicines Quantity\n";
        cout<<"\t\t\t\t\t\t\t7:Return to main menu";
		cout<<"\n\n\t\t\t\t\t\t\tEnter the choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1: m.add_medicine(); break;
			case 2: m.search_medicine(); break;
			case 3: m.delete_medicine(); break;
			case 4: m.display_medicine();break;
			case 5: m.modify_medicine();break;
			case 6: m.update_stock();break;
			case 7: return;
			default:
			cout<<"\nInvalid choice !\n"; exit(0);	
		}
	}
}

// order page-----------------------------------------------------------------

//Record specification
class order{
public:
char ind[5],med_id[5],medi_name[15],Qty[15],ord_id[10];
char stkid[5],stkname[15],m_date[15],ex_date[15],pri[10],com[10];
char status[15];
char pen[15]="pending";
void add_order();
void search_order();
//int check_medID(char *);
void delete_order();
void display_order();
int get_id(char *);
void modify_order();
void order_module();
int get_num_order();
void confirm_order();
void retrieve_order(char *);
}ordrec[20];
int no4;
int order::get_num_order()
{
int I=0;
fstream file2;

	
	file2.open("record_order.txt",ios::in);
	if(!file2)
	{
		return 0;
	}
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(ordrec[I].ind,5,'|');
		file2.getline(ordrec[I].ord_id,10,'|');
		file2.getline(ordrec[I].med_id,5,'|');
		file2.getline(ordrec[I].medi_name,15,'|');
		file2.getline(ordrec[I].Qty,15,'|');
		file2.getline(ordrec[I].status,15,'\n');
		I++; 	
 	}
	I--;
	file2.close();
	return I;
}
void order::retrieve_order(char id[])
{
	order m;

	no4 = m.get_num_order();
	for(int i=0;i<no4;i++)
 	{
		if(strcmp(ordrec[i].ind,id)==0) 
	 	{
		cout<<"\n\n"<<"Company Products details : ";
		cout<<"\nord_id    :"<<ordrec[i].ord_id<<"\nMedicine id   :"<<ordrec[i].med_id<<"\nmedi_name   :"<<ordrec[i].medi_name<<"\nQuantity  :" <<ordrec[i].Qty<<"\n Status :"<<ordrec[i].status<<"\n";
		break;
	 	}
 	}
}


void order::add_order()
{
	char buf1[100],buf2[20];
	fstream file1,file2;
	int I,cnt;
	order m;
	cnt=get_num_order();

	file1.open("index_order.txt",ios::out|ios::app);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	file2.open("record_order.txt",ios::out|ios::app);
	if(!file2)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	int c;
	fstream app,in,out;
	app.open("number.txt",ios::in);
	if(!app)
	{
		cout<<"cannot read the file\n";
		exit(0);
	}
	app>>c;
	app.close();
	in.open("number.txt",ios::trunc|ios::out);
	c+=1;
	in<<c;
	in.close();

	cout<<"\nEnter the number of Medicines to order : ";
	cin>>no4;
	cout<<"\nEnter the details :\n"; 

	for(I=cnt; I<(cnt+no4); I++)
   {                  
		
	while(1)
	   {     
	   	cout<<"\nEnter the Drug ID 							:";
		cin>>m.med_id;
		if(get_id(m.med_id)==0)
		{
			cout<<"Record with medicine id "<<m.med_id<<" is not present in the stock";
		}
		else
		{
			break;
		}

	    } 
		cout<<"\nmedi_name : ";
		cin>>m.medi_name;
        cout<<"\nQuantity : ";
		cin>>m.Qty;

		app.open("number.txt",ios::in);
		if(!app)
		{
			cout<<"cannot read the file\n";
			exit(0);
		}
		app>>c;
		app.close();
		in.open("number.txt",ios::trunc|ios::out);
		c+=1;
		in<<c;
		in.close();

		sprintf(buf2,"%d|%d\n",c,I);
		file1<<buf2;

		sprintf(buf1,"%d|%d|%s|%s|%s|%s\n",I,c,m.med_id,m.medi_name,m.Qty,m.pen);
		file2<<buf1;
	}

	cout<<"\n\nOrder Placed Successfully!!!\n";
		file1.close();
		file2.close();
}

int order::get_id(char id[])
{
	fstream app;
	order o;
	app.open("record_stock.txt",ios::in);
	while(!app.eof())
	{
		app.getline(o.ind,5,'|');
		app.getline(o.stkid,5,'|');
		app.getline(o.stkname,15,'|');
		app.getline(o.m_date,15,'|');
		app.getline(o.ex_date,15,'|');
		app.getline(o.pri,5,'|');
		app.getline(o.com,15,'\n');
	
		if(strcmp(o.stkid,id)==0)
		{
			return 1;
		}
	}
	app.close();
}

void order::search_order()
{
int I,flag1;
char med_no[5],id[10],record_id[5];
fstream file1;
order m;

	cout<<"\nPlease enter the ord_id of the medicine";
	cout<<" whose record is to be displayed\n";
	cin>>id;
	file1.open("index_order.txt",ios::in); 
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag1=0;
	while(!file1.eof())
	{
		file1.getline(record_id,5,'|');
		file1.getline(med_no,5,'\n');    
		if(strcmp(id,record_id)==0)
		{
			m.retrieve_order(med_no);         
			flag1=1;                  
			break;
		}
	}
	if(!flag1)
	cout<<"\nRecord search failed !!\n"; 
	file1.close();
}

void delete_order_record(char ID[])
{
int I=0;
fstream file1,file2;
order m;
	no4 = m.get_num_order();	
	int flag=-1;
	for(I=0;I<no4;I++)       //Check for the record's existence
	{
		if(strcmp(ordrec[I].ind,ID)==0)
		{
			flag=I;
			break;
		}	

	}

	if(flag==-1)                //Record not found
	{
		cout<<"\nError !\n";
		return;
	}
	if(flag==(no4-1))            //Delete found last record
	{
		no4--;
		cout<<"\nDeleted !\n";
		
	}
	else
	{
		for(I=flag;I<no4;I++)
		{
			ordrec[I] = ordrec[I+1];
		}
		no4--;
		cout<<"\nDeleted !\n";
	}

	file1.open("index_order.txt",ios::out);  
	file2.open("record_order.txt",ios::out);  
	for(I=0;I<no4;I++)                   
	{                                   
		file1<<ordrec[I].med_id<<"|"<<I<<"\n";
		file2<<I<<"|"<<ordrec[I].ord_id<<"|"<<ordrec[I].med_id<<"|"<<ordrec[I].medi_name <<"|"<<ordrec[I].Qty<<"|"<<ordrec[I].status<<"\n";
	}
	file1.close();
	file2.close();
	return;
}



void order::delete_order()
{
int I,flag;
char med_no[5],id[10],record_id[5];
fstream file1;

	cout<<"\nPlease enter the ord_id of the medicine ";
	cout<<" whose record is to be deleted\n";
	cin>>id;
	file1.open("index_order.txt",ios::in);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag=0;

	while(!file1.eof())
	{
		file1.getline(record_id,5,'|');      //Search index file and
		file1.getline(med_no,5,'\n');       //call deletion
		//if index found
		if(strcmp(id,record_id)==0)
		{
			delete_order_record(med_no); 
			flag=1;
			break;
		}
	}
	if(!flag)
	cout<<"\nDeletion failed !\n"; 
	file1.close();
	
	
}

void order::modify_order()
{
	fstream in;
	char ID[10];
	int i=0,j;
	order m1[100];
	
	in.open("record_order.txt",ios::in);
	if(!in)
	{
		cout<<"file cannot be opened \n";
		exit(0);
	}
	cout<<"Enter the medicine ID\n";
	cin>>ID;

	while(!in.eof())
	{
		in.getline(m1[i].ind,5,'|');
		in.getline(m1[i].ord_id,10,'|');
		in.getline(m1[i].med_id,5,'|');
		in.getline(m1[i].medi_name,15,'|');
		in.getline(m1[i].Qty,15,'|');
		in.getline(m1[i].status,15,'\n');
		i++;

	}
	i--;
	for(j=0;j<i;j++)
	{
		if(strcmp(ID,m1[j].ord_id)==0)
		{
			cout<<"\n Medicine details before printing";
			cout<<"------------------------------------";
			cout<<"\nIndex      	   :"<<m1[j].ind;
			cout<<"\nOrder ID		   :"<<m1[j].ord_id;
			cout<<"\nMedicine ID  	   :"<<m1[j].med_id;
			cout<<"\nMedicine Name 	   :"<<m1[j].medi_name;
			cout<<"\nQuantity		  :"<<m1[j].Qty;
			cout<<"\nStatus		  	   :"<<m1[j].status;

			cout<<"\n\n Enter the  medicine modification details";
			cout<<"\n----------------------------------------------\n";
			cout<<"\nMedicine Name 	   :";	cin>>m1[j].medi_name;
			cout<<"\nQuantity		   :";	cin>>m1[j].Qty;
			break;

		}
	}
	if(j==i)
    {
        cout<<"\nThe record with Medicine_ID "<<ID<<" is not present"; 
        return;
    }

	in.close();

	fstream out;
	out.open("record_order.txt",ios::out);
	if(!out)
	{
		cout<<"\n unable to open the file in output mode";
		return;
	}
	
	for(j=0;j<i;j++)
	{
		out<<m1[j].ind<<'|'<<m1[j].ord_id<<'|'<<m1[j].med_id<<'|'<<m1[j].medi_name<<'|'<<m1[j].Qty<<"|"<<m1[j].status<<"\n";
	}
	out.close();
	
}

void order::display_order()
{
fstream file2;
order m;
	
	file2.open("record_order.txt",ios::in);
cout<<"\n\n"<<"medicine details : \n";
cout<<"Index"<<"\t"<<"Order_ID"<<"\t"<<"Medi_id"<<"\t\t"<<"medi_name"<<"\t"<<"Quantity"<<"\t"<<"status"<<endl; 
cout<<"==============================================================================\n";
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(m.ind,5,'|');
		file2.getline(m.ord_id,10,'|');
		file2.getline(m.med_id,15,'|');
		file2.getline(m.medi_name,15,'|');
		file2.getline(m.Qty,15,'|');
		file2.getline(m.status,15,'\n');
cout<<m.ind<<"\t"<<m.ord_id<<"\t\t"<<m.med_id<<"\t\t"<<m.medi_name<<"\t"<<m.Qty<<"\t\t"<<m.status<<"\n";
	 	
 	}
	 cout<<"==============================================================================\n";
	file2.close();

}



void order::confirm_order()
{
	fstream in;
	char ID[5];
	int i=0,j;
	order m1[100];
	
	in.open("record_order.txt",ios::in);
	if(!in)
	{
		cout<<"file cannot be opened \n";
		exit(0);
	}
	cout<<"Enter the order ID to confirm the order \n";
	cin>>ID;

	while(!in.eof())
	{
		in.getline(m1[i].ind,5,'|');
		in.getline(m1[i].ord_id,10,'|');
		in.getline(m1[i].med_id,5,'|');
		in.getline(m1[i].medi_name,15,'|');
		in.getline(m1[i].Qty,15,'|');
		in.getline(m1[i].status,15,'\n');
		i++;

	}
	i--;
	for(j=0;j<i;j++)
	{
		if(strcmp(ID,m1[j].ord_id)==0)
		{
			cout<<"\n Medicine details before printing";
			cout<<"------------------------------------";
			cout<<"\nIndex      	   :"<<m1[j].ind;
			cout<<"\nOrder ID      	   :"<<m1[j].ord_id;
			cout<<"\nMedicine ID  	   :"<<m1[j].med_id;
			cout<<"\nMedicine Name 	   :"<<m1[j].medi_name;
			cout<<"\nMedicine Quantity  :"<<m1[j].Qty;
			cout<<"\nStatus		  	   :"<<m1[j].status;

			cout<<"\n\nEnter the status of the order";
			cout<<"\n\n Status		   :";	cin>>m1[j].status;
			break;

		}
	}
	if(j==i)
    {
        cout<<"\nThe record with Order_ID "<<ID<<" is not present"; 
        return;
    }

	in.close();

	fstream out;
	out.open("record_order.txt",ios::out);
	if(!out)
	{
		cout<<"\n unable to open the file in output mode";
		return;
	}
	
	for(j=0;j<i;j++)
	{
		out<<m1[j].ind<<'|'<<m1[j].ord_id<<'|'<<m1[j].med_id<<'|'<<m1[j].medi_name<<'|'<<m1[j].Qty<<"|"<<m1[j].status<<"\n";
	}
	out.close();
	
}


// stock Module------------------------------------------------------------
class stock{
public:
char ind[5],stock_id[5],stock_name[15],manu_date[15],exp_date[15],Company[15],mrp[5],qty[15],date[10],tym[10];
char status[10];
void add_stock();
void search_stock();
void delete_stock();
void display_stock();
void modify_stock();
void medicine_stock();
int get_num_stock();
void confirm_order();
int checkID(char *);
void modify_stocks();
}stockrec[20];
int no2;
int stock::get_num_stock()
{
int I=0;
fstream file2;
	file2.open("record_stock.txt",ios::in);
	if(!file2)
	{
		return 0;
	}
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(stockrec[I].ind,5,'|');
		file2.getline(stockrec[I].stock_id,5,'|');
		file2.getline(stockrec[I].stock_name,15,'|');
		file2.getline(stockrec[I].manu_date,15,'|');
		file2.getline(stockrec[I].exp_date,15,'|');
		file2.getline(stockrec[I].mrp,5,'|');
		file2.getline(stockrec[I].Company,15,'\n');
		I++; 	
 	}
	I--;
	file2.close();
	return I;
}
void retrieve_stock(char st_no[])
{
	stock d;

	no2 = d.get_num_stock();
	for(int i=0;i<no2;i++)
 	{
		if(strcmp(stockrec[i].ind,st_no)==0) 
	 	{
		cout<<"\n\n"<<"Medicine stock details : ";
		cout<<"\nstock_ID    :"<<stockrec[i].stock_id<<"\nstock_Name   :"<<stockrec[i].stock_name<<"\nmanu_date  :" <<stockrec[i].manu_date<<"\nexp_date    :"<<stockrec[i].exp_date<<"\nMRP :"<<stockrec[i].mrp<<"\nCompany :"<<stockrec[i].Company<<"\n";
		break;
	 	}
 	}
}

int stock::checkID(char ID[])
{
	fstream app;
	stock d;
	app.open("record_stock.txt",ios::in);
	while(!app.eof())
	{
		app.getline(d.ind,5,'|');
		app.getline(d.stock_id,5,'|');
		app.getline(d.stock_name,15,'|');
		app.getline(d.manu_date,15,'|');
		app.getline(d.exp_date,15,'|');
		app.getline(d.mrp,5,'|');
		app.getline(d.Company,15,'\n');
	
		if(strcmp(d.stock_id,ID)==0)
		{
			return 1;
		}
	}
	app.close();
	
}
void stock::add_stock()
{
char buf1[100],buf2[20];
fstream file1,file2;
int I,cnt;
stock s;

	cnt=get_num_stock();

	file1.open("index_stock.txt",ios::out|ios::app);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	file2.open("record_stock.txt",ios::out|ios::app);
	if(!file2)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	cout<<"\nEnter the no. of Medicines : ";
	cin>>no2;
	cout<<"\nEnter the details :\n"; 

	for(I=cnt; I<(cnt+no2); I++)
   {                  
		
		while(1)
	   {     
	   	cout<<"\nEnter the stock ID 	:";   cin>>s.stock_id;
		if(s.checkID(s.stock_id)==1)
		{
			cout<<"Record with medicine id "<<s.stock_id<<" is already present";
		}
		else
		{
			break;
		}
	   }
	   	cout<<"\nMedicine_Name        : ";    cin>>s.stock_name;
        cout<<"\nmanu_date dd/mm/yyyy         : ";    cin>>s.manu_date;
		cout<<"\nexp_date  dd/mm/yyyy          : ";    cin>>s.exp_date;
		cout<<"\nCompany       : ";    cin>>s.Company;
		cout<<"\nMRP            : ";    cin>>s.mrp;

		sprintf(buf2,"%s|%d\n",s.stock_id,I);
		file1<<buf2;

		sprintf(buf1,"%d|%s|%s|%s|%s|%s|%s\n",I,s.stock_id,s.stock_name,s.manu_date,s.exp_date,s.mrp,s.Company);
		file2<<buf1;
	}
	cout<<"\n\nStock Ordered Successfully!!!\n";
		file1.close();
		file2.close();
}

void stock::search_stock()
{
int I,flag1;
char st_no[5],st_id[5],record_id[5];
fstream file1;


	cout<<"\nPlease enter the stock_id of the stock";
	cout<<" whose record is to be displayed\n";
	cin>>st_id;
	file1.open("index_stock.txt",ios::in); 
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag1=0;
	while(!file1.eof())
	{
		file1.getline(record_id,5,'|');
		file1.getline(st_no,5,'\n');    
		if(strcmp(st_id,record_id)==0)
		{
			retrieve_stock(st_no);         
			flag1=1;                  
			break;
		}
	}
	if(!flag1)
	cout<<"\nRecord search failed !!\n"; 
	file1.close();
}

void delete_stock_record(char ID[])
{
int I=0;
fstream file1,file2;
stock m;
	no2 = m.get_num_stock();	
	int flag=-1;
	for(I=0;I<no2;I++)       //Check for the record's existence
	{
		if(strcmp(stockrec[I].ind,ID)==0)
		{
			flag=I;
			break;
		}	

	}

	if(flag==-1)                //Record not found
	{
		cout<<"\nError !\n";
		return;
	}
	if(flag==(no2-1))            //Delete found last record
	{
		no2--;
		cout<<"\nDeleted !\n";
		
	}
	else
	{
		for(I=flag;I<no2;I++)
		{
			stockrec[I] = stockrec[I+1];
		}
		no2--;
		cout<<"\nDeleted !\n";
	}

	file1.open("index_stock.txt",ios::out);  
	file2.open("record_stock.txt",ios::out);  
	for(I=0;I<no2;I++)                   
	{                                   
		file1<<stockrec[I].stock_id<<"|"<<I<<"\n";
		file2<<I<<"|"<<stockrec[I].stock_id<<"|"<<stockrec[I].stock_name <<"|"<<stockrec[I].manu_date<<"|"<<stockrec[I].exp_date<<"|"<<stockrec[I].mrp<<"|"<<stockrec[I].Company<<"\n";
	}
	file1.close();
	file2.close();
	return;
}



void stock::delete_stock()
{
int I,flag;
char st_no[5],stock_id[5],record_id[5];
fstream file1;

	cout<<"\nPlease enter the stock_id of the Stock to delete the record :";
	cin>>stock_id;
	file1.open("index_stock.txt",ios::in);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag=0;

	while(!file1.eof())
	{
		file1.getline(record_id,5,'|');      //Search index file and
		file1.getline(st_no,5,'\n');       //call deletion
		//if index found
		if(strcmp(stock_id,record_id)==0)
		{
			delete_stock_record(st_no); 
			flag=1;
			break;
		}
	}
	if(!flag)
	cout<<"\nDeletion failed !\n"; 
	file1.close();
	
	
}

void stock::modify_stock()
{
	fstream in;
	char ID[5];
	int i=0,j;
	stock d1[100];
	
	in.open("record_stock.txt",ios::in);
	if(!in)
	{
		cout<<"file cannot be opened \n";
		exit(0);
	}
	cout<<"Enter the stock ID\n";
	cin>>ID;

	while(!in.eof())
	{
		in.getline(d1[i].ind,5,'|');
		in.getline(d1[i].stock_id,5,'|');
		in.getline(d1[i].stock_name,15,'|');
		in.getline(d1[i].manu_date,15,'|');
		in.getline(d1[i].exp_date,15,'|');
		in.getline(d1[i].mrp,5,'|');
		in.getline(d1[i].Company,15,'\n');
		i++;

	}
	i--;
	for(j=0;j<i;j++)
	{
		if(strcmp(ID,d1[j].stock_id)==0)
		{
			cout<<"\n Medicine details before printing\n";
			cout<<"------------------------------------";
			cout<<"\nIndex      	        :"<<d1[j].ind;
			cout<<"\nMedicine ID  	        :"<<d1[j].stock_id;
			cout<<"\nMedicine Name 	        :"<<d1[j].stock_name;
			cout<<"\nmanu_date              :"<<d1[j].manu_date;
			cout<<"\nexp_date  	            :"<<d1[j].exp_date;
			cout<<"\nMRP                    :"<<d1[j].mrp;
			cout<<"\nContact No		  	    :"<<d1[j].Company;
            cout<<"\n----------------------------------------------\n";


			cout<<"\n\n Enter the  Stock modification details";
			cout<<"\n----------------------------------------------------\n";
			cout<<"\nMedicine Name 	            :";	cin>>d1[j].stock_name;
			cout<<"\nmanu_date                  :";	cin>>d1[j].manu_date;
			cout<<"\nexp_date  	                :";	cin>>d1[j].exp_date;
			cout<<"\nMRP						:"; cin>>d1[j].mrp;
			cout<<"\nContact No		  	        :";	cin>>d1[j].Company;
			
            cout<<"\n-----------------------------------------------------\n";
			break;

		}
	}
	if(j==i)
    {
        cout<<"\nThe record with Stock_ID "<<ID<<" is not present"; 
        return;
    }

	in.close();
	fstream out;
	out.open("record_stock.txt",ios::out);
	if(!out)
	{
		cout<<"\n unable to open the file in output mode";
		return;
	}
	
	for(j=0;j<i;j++)
	{
		out<<d1[j].ind<<'|'<<d1[j].stock_id<<'|'<<d1[j].stock_name<<'|'<<d1[j].manu_date<<"|"<<d1[j].exp_date<<'|'<<d1[j].mrp<<'|'<<d1[j].Company<<'\n';
	}
	out.close();
	
}

void stock::display_stock()
{
fstream file2;
stock d;
	
	file2.open("record_stock.txt",ios::in);
	cout<<"\n\n"<<"Agency Stock details : \n";
	cout<<"======================================================================================"<<endl; 
	cout<<"Index"<<"\t"<<"stock_id"<<"\t"<<"stock_name"<<"\t"<<"manu_date"<<"\t"<<"exp_date"<<"\t"<<"MRP"<<"\t"<<"Company"<<"\t"<<endl;
	cout<<"======================================================================================="<<endl; 
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(d.ind,5,'|');
		file2.getline(d.stock_id,5,'|');
		file2.getline(d.stock_name,15,'|');
		file2.getline(d.manu_date,15,'|');
		file2.getline(d.exp_date,15,'|');
		file2.getline(d.mrp,5,'|');
		file2.getline(d.Company,15,'\n');
	cout<<d.ind<<"\t"<<d.stock_id<<"\t\t"<<d.stock_name<<"\t\t"<<d.manu_date<<"\t"<<d.exp_date<<"\t"<<d.mrp<<"\t"<<d.Company<<"\t"<<"\n";
	 	
 	}
	cout<<"======================================================================================="<<endl; 
	file2.close();

}

void stock_module()
{
	order m;
    stock d;
	int choice;
	
	for(;;)
	{
		//d.display_stock();
		cout<<"\n\n\n";
		// d.display_stock();
		cout<<"\t\t\t\t\t\t\t======================\n";
		cout<<"\t\t\t\t\t\t\t  AGENCY STOCK MANAGEMENT\n";
		cout<<"\t\t\t\t\t\t\t======================\n";
		cout<<"\n\t\t\t\t\t\t\t1:Add Stock\n";
		cout<<"\t\t\t\t\t\t\t2:Search Stock\n";
		cout<<"\t\t\t\t\t\t\t3:Display Stock\n";
		cout<<"\t\t\t\t\t\t\t4:Update Stock\n";
		cout<<"\t\t\t\t\t\t\t5:Delete Stock\n";
		cout<<"\n\n\t\t\t\t\t\t\t========================\n";
		cout<<"\t\t\t\t\t\t\t  ADMIN ORDER MANAGEMENT\n";
		cout<<"\t\t\t\t\t\t\t========================\n";
		cout<<"\t\t\t\t\t\t\t6:Admin Orders\n";
		cout<<"\t\t\t\t\t\t\t7:Confirm Admin Orders\n";
		cout<<"\t\t\t\t\t\t\t8: Exit\n\n";
		cout<<"\t\t\t\t\t\t\tEnter the choice\n";
		
		cin>>choice;
		switch(choice)
		{
			case 1: d.add_stock(); break;
			case 2: d.search_stock(); break;
			case 3: d.display_stock();break;
			case 4: d.modify_stock(); break;
			case 5: d.delete_stock();break;
			case 6: m.display_order(); break;
			case 7: m.confirm_order();break;
			case 8: return;
			default:
			cout<<"\nInvalid choice !\n"; exit(0);	
		}
	}
}
void agency()
{
	order m;
    stock d;
	int choice;
	
	for(;;)
	{
		//d.display_stock();
		cout<<"\n\n\n";
		// d.display_stock();
		cout<<"\t\t\t\t\t\t\t======================\n";
		cout<<"\t\t\t\t\t\t\t  AGENCY STOCK MANAGEMENT\n";
		cout<<"\t\t\t\t\t\t\t======================\n";
		cout<<"\n\t\t\t\t\t\t\t1:Add Stock\n";
		cout<<"\t\t\t\t\t\t\t2:Search Stock\n";
		cout<<"\t\t\t\t\t\t\t3:Display Stock\n";
		cout<<"\t\t\t\t\t\t\t4:Update Stock\n";
		cout<<"\t\t\t\t\t\t\t5:Delete Stock\n";
		cout<<"\t\t\t\t\t\t\t6:Admin Orders\n";
		cout<<"\t\t\t\t\t\t\t7:Confirm Admin Orders\n";
		cout<<"\t\t\t\t\t\t\t8: Exit\n\n";
		cout<<"\t\t\t\t\t\t\tEnter the choice\n";
		
		cin>>choice;
		switch(choice)
		{
			case 1: d.add_stock(); break;
			case 2: d.search_stock(); break;
			case 3: d.display_stock();break;
			case 4: d.modify_stock(); break;
			case 5: d.delete_stock();break;
			case 6: m.display_order(); break;
			case 7: m.confirm_order();break;
			case 8: return;
			default:
			cout<<"\nInvalid choice !\n"; exit(0);	
		}
	}
}

// Customer Page--------------------------------------------------------


//Record specification
class customer{
public:
char ind[5],customer_ID[5],customer_name[15],manu_date[15],address[15],Company[15];
void add_customer();
void search_customer();
void delete_customer();
void display_customer();
void modify_customer();
void medicine_customer();
int get_num_customer();


}customerrec[20];
int no3;
int customer::get_num_customer()
{
int I=0;
fstream file2;

	
	file2.open("record_customer.txt",ios::in);
	if(!file2)
	{
		return 0;
	}
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(customerrec[I].ind,5,'|');
		file2.getline(customerrec[I].customer_ID,5,'|');
		file2.getline(customerrec[I].customer_name,15,'|');
		file2.getline(customerrec[I].manu_date,15,'|');
		file2.getline(customerrec[I].Company,15,'|');
		file2.getline(customerrec[I].address,15,'\n');
		I++; 	
 	}
	I--;
	file2.close();
	return I;
}
void retrieve_customer(char customer_no[])
{
	customer d;
	no3 = d.get_num_customer();
	for(int i=0;i<no3;i++)
 	{
		if(strcmp(customerrec[i].ind,customer_no)==0) 
	 	{
		cout<<"\n\n"<<"Medicine Customer details : ";
		cout<<"\ncustomer_ID\t\t\t:"<<customerrec[i].customer_ID<<"\ncustomer_Name\t\t\t:"<<customerrec[i].customer_name<<"\nmanu_date\t\t\t\t:" <<customerrec[i].manu_date<<"\nContact_No\t\t\t:"<<customerrec[i].Company<<"\nAddress\t\t\t:"<<customerrec[i].address<<"\n";
		break;
	 	}
 	}
}


void customer::add_customer()
{
char buf1[100],buf2[20];
fstream file1,file2;
int I,cnt;
customer m;

	cnt=get_num_customer();

	file1.open("index_customer.txt",ios::out|ios::app);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	file2.open("record_customer.txt",ios::out|ios::app);
	if(!file2)
	{
		cout<<"\nError !\n";
		exit(0);
	}

		cout<<"\nEnter the no. of Customer 					: ";
		cin>>no3;
		cout<<"\nEnter the details 							:\n\n"; 

	for(I=cnt; I<(cnt+no3); I++)
   {                  
		cout<<"\nEnter the Customer_Name          			: ";    
		cin>>m.customer_name;
		cout<<"\nEnter the Customer_ID            			: ";    
		cin>>m.customer_ID;
        cout<<"\nEnter the Customer's manu_date M/F             : ";    
		cin>>m.manu_date;
		cout<<"\nEnter the Customer's Contact no.           : ";    
		cin>>m.Company;
		cout<<"\nEnter the customer's residential address   : ";    
		cin>>m.address;
		

		sprintf(buf2,"%s|%d\n",m.customer_ID,I);
		file1<<buf2;

		sprintf(buf1,"%d|%s|%s|%s|%s|%s\n",I,m.customer_ID,m.customer_name,m.manu_date,m.Company,m.address);
		file2<<buf1;
	}
		file1.close();
		file2.close();
}

void customer::search_customer()
{
int I,flag1;
char customer_no[5],customerid[5],record_id[5];
fstream file1;


	cout<<"\nPlease enter the customer_ID of the customer";
	cout<<" whose record is to be displayed\n";
	cin>>customerid;
	file1.open("index_customer.txt",ios::in); 
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag1=0;
	while(!file1.eof())
	{
		file1.getline(record_id,5,'|');
		file1.getline(customer_no,5,'\n');    
		if(strcmp(customerid,record_id)==0)
		{
			retrieve_customer(customer_no);         
			flag1=1;                  
			break;
		}
	}
	if(!flag1)
	cout<<"\nRecord search failed !!\n"; 
	file1.close();
}

void delete_customer_record(char ID[])
{
int I=0;
fstream file1,file2;
customer m;
	no3 = m.get_num_customer();	
	int flag=-1;
	for(I=0;I<no3;I++)       //Check for the record's existence
	{
		if(strcmp(customerrec[I].ind,ID)==0)
		{
			flag=I;
			break;
		}	

	}

	if(flag==-1)                //Record not found
	{
		cout<<"\nError !\n";
		return;
	}
	if(flag==(no3-1))            //Delete found last record
	{
		no3--;
		cout<<"\nDeleted !\n";
		
	}
	else
	{
		for(I=flag;I<no3;I++)
		{
			customerrec[I] = customerrec[I+1];
		}
		no3--;
		cout<<"\nDeleted !\n";
	}

	file1.open("index_customer.txt",ios::out);  
	file2.open("record_customer.txt",ios::out);  
	for(I=0;I<no3;I++)                   
	{                                   
		file1<<customerrec[I].customer_ID<<"|"<<I<<"\n";
		file2<<I<<"|"<<customerrec[I].customer_ID<<"|"<<customerrec[I].customer_name <<"|"<<customerrec[I].manu_date<<"|"<<customerrec[I].Company<<"|"<<customerrec[I].address<<"\n";
	}
	file1.close();
	file2.close();
	return;
}


void customer::delete_customer()
{
int I,flag;
char customer_no[5],customer_id[5],record_id[5];
fstream file1;

	cout<<"\nPlease enter the customer_ID of the customer ";
	cout<<" whose record is to be deleted\n";
	cin>>customer_id;
	file1.open("index_customer.txt",ios::in);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag=0;

	while(!file1.eof())
	{
		file1.getline(record_id,5,'|');      //Search index file and
		file1.getline(customer_no,5,'\n');       //call deletion
		//if index found
		if(strcmp(customer_id,record_id)==0)
		{
			delete_customer_record(customer_no); 
			flag=1;
			break;
		}
	}
	if(!flag)
	cout<<"\nDeletion failed !\n"; 
	file1.close();
	
	
}

void customer::modify_customer()
{
	fstream in;
	char ID[5];
	int i=0,j;
	customer d1[100];
	
	in.open("record_customer.txt",ios::in);
	if(!in)
	{
		cout<<"file cannot be opened \n";
		exit(0);
	}
	cout<<"Enter the customer ID\n";
	cin>>ID;

	while(!in.eof())
	{
		in.getline(d1[i].ind,5,'|');
		in.getline(d1[i].customer_ID,5,'|');
		in.getline(d1[i].customer_name,15,'|');
		in.getline(d1[i].manu_date,15,'|');
		in.getline(d1[i].Company,15,'|');
		in.getline(d1[i].address,15,'\n');
		i++;

	}
	i--;
	for(j=0;j<i;j++)
	{
		if(strcmp(ID,d1[j].customer_ID)==0)
		{
			cout<<"\n Customer details before modification\n";
			cout<<"------------------------------------";
			cout<<"\nIndex			:";
			cout<<d1[j].ind;
			cout<<"\nCustomer ID	:";
			cout<<d1[j].customer_ID;
			cout<<"\nCustomer Name	:";
			cout<<d1[j].customer_name;
			cout<<"\nmanu_date         :";
			cout<<d1[j].manu_date;
			cout<<"\nContact No		:";
			cout<<d1[j].Company;
			cout<<"\nAddress		:";
			cout<<d1[j].address;
			
            cout<<"\n----------------------------------------------\n";


			cout<<"\n\n Enter the customer details for modification ";
			cout<<"\n----------------------------------------------------\n";
			cout<<"customer Name		:";	
			cin>>d1[j].customer_name;
			cout<<"manu_date				:";	
			cin>>d1[j].manu_date;
			cout<<"Contact No			:";	
			cin>>d1[j].Company;
			cout<<"address				:";	
			cin>>d1[j].address;
			
            cout<<"\n-----------------------------------------------------\n";
			break;

		}
	}
	if(j==i)
    {
        cout<<"\nThe record with customer_ID "<<ID<<" is not present"; 
        return;
    }

	in.close();

	fstream out;
	out.open("record_customer.txt",ios::out);
	if(!out)
	{
		cout<<"\n unable to open the file in output mode";
		return;
	}
	
	for(j=0;j<i;j++)
	{
		out<<d1[j].ind<<'|'<<d1[j].customer_ID<<'|'<<d1[j].customer_name<<'|'<<d1[j].manu_date<<'|'<<d1[j].Company<<"|"<<d1[j].address<<'\n';
	}
	out.close();
}

void customer::display_customer()
{
fstream file2;
customer d;
	
	file2.open("record_customer.txt",ios::in);
	cout<<"\n\n\n";
	
	cout<<"==============================================================================================\n";
	cout<<"Index"<<"\t\t"<<"customer_ID"<<"\t"<<"customer_name"<<"\t"<<"Gender"<<"\t"<<"Contact"<<"\t"<<"Address"<<"\t"<<endl;
	cout<<"==============================================================================================\n";
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(d.ind,5,'|');
		file2.getline(d.customer_ID,5,'|');
		file2.getline(d.customer_name,15,'|');
		file2.getline(d.manu_date,15,'|');
		file2.getline(d.Company,15,'|');
		file2.getline(d.address,15,'\n');
		cout<<d.ind<<"\t\t"<<d.customer_ID<<"\t\t"<<d.customer_name<<"\t\t"<<d.manu_date<<"\t\t"<<d.Company<<"\t"<<d.address<<"\n";
	 	
 	}
	 cout<<"==============================================================================================\n";
	file2.close();

}

void customer_module()
{
    customer c;
int choice;
c.display_customer();
	for(;;)
	{
		cout<<"\n\n\n";
		cout<<"\t\t\t\t\t\t\t===============\n";
		cout<<"\t\t\t\t\t\t\tCustomer Module\n";
		cout<<"\t\t\t\t\t\t\t================\n";
		cout<<"\t\t\t\t\t\t\t1:Add Customer\n";
		cout<<"\t\t\t\t\t\t\t2:Search Customer\n";
		cout<<"\t\t\t\t\t\t\t3:Delete Customer\n";
		cout<<"\t\t\t\t\t\t\t4:Display Customer\n";
		cout<<"\t\t\t\t\t\t\t5.Modify Customer\n";
        cout<<"\t\t\t\t\t\t\t6: Return to main menu\n";
		cout<<"\t\t\t\t\t\t\tEnter the choice\t:";
		cin>>choice;
		switch(choice)
		{
			case 1: c.add_customer(); break;
			case 2: c.search_customer(); break;
			case 3: c.delete_customer(); break;
			case 4: c.display_customer();break;
			case 5: c.modify_customer();break;
			case 6: return;
			default:
			cout<<"\nInvalid choice !\n"; exit(0);	
		}
	}
}

// Billing module---------------------------------------------------------

class bill
{
	private: char cus_id[5],med_id[5],name[50][50],cus_name[10];
	int num;
	float qty[5];
	float mrp[5];
	int tprice[5];
	int i;
	int vatprice[5];

	public: void addbill();
	void billgene();
	void billcalcu();
	void output();
	int checkcustomer(char *);
};

void bill::addbill()
{
	while (1)
   {
    cout<<"Enter the Customer ID	:";
    cin>>cus_id;
	if(checkcustomer(cus_id)==1)
			{
				break;
			}
		else
			{
				cout<<"Customer ID with"<<cus_id<<" is not present";
			}
    }
	cout<<"\n\nEnter the name of the customer to verify  :";
	cin>>cus_name;

	cout<<"\n Enter the number of items :";
	cin>>num;
	for(int i=0;i<num;i++)
	{
		cout<<"\nEnter Medicine ID :";
		cin>>med_id;
		cout<<"Enter medicine name :";
		cin>>name[i];
		cout<<"Enter the medicine quantity :";
		cin>>qty[i];
		cout<<"Enter the medicine price :";
		cin>>mrp[i];
		tprice[i]=qty[i]*mrp[i];
	}
	
}

void bill::billcalcu()
{
	addbill();

	for(int i=0;i<num;i++)
	{
		if(mrp[i]<=1000.00)
		{
			vatprice[i]=tprice[i]+(0.03*tprice[i]);
		}
		else
		{
			vatprice[i]=tprice[i]+(0.1*tprice[i]);
		}
	}
}

void bill::billgene()
{
	float cash=0,amount=0,qtyt=0,sumt=0;
	for(int i=0;i<num;i++)
	{
	       sumt+=tprice[i];
		   amount+=vatprice[i];
		   qtyt+=qty[i];
	}
	fstream file1;
	file1.open("pracbill.txt",ios::out|ios::app);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	time_t my_time = time(NULL);

	// bill number---------------------------------
	int b;
	fstream app,in;
	app.open("billnumber.txt",ios::in); //read mode
	if(!app)
	{
		cout<<"cannot read the file\n";
		exit(0);
	}
	app>>b;
	app.close();
	in.open("billnumber.txt",ios::trunc|ios::out);
	b+=1;
	in<<b;
	in.close();
	//bill number---------------------------------------------
	file1<<endl<<"Date & Time :"<<ctime(&my_time);
	file1<<endl<<"Bill Number :"<<b<<endl;
	file1<<endl<<"Customer_ID :"<<cus_id<<endl;
	file1<<endl<<"Customer_Name :"<<cus_name<<endl;
	file1<<"-------------------------------------------------------------"<<endl;
	cout<<"\n";
	cout<<"Name of Medicine\tQuantity\tPrice\tTotal Price\n";
	for(int i=0;i<num;i++)
	{
		file1<<"Medicine name : "<<name[i]<<" Quantity : "<<qty[i]<<" Price : "<<mrp[i]<<" Total Price :"<<tprice[i]<<endl;
		cout<<name[i]<<"\t\t"<<qty[i]<<"\t\t"<<mrp[i]<<"\t\t"<<tprice[i]<<"\n"<<endl;
	}
	file1<<"-------------------------------------------------------------"<<endl;
	file1<<"\t\t\t\tThe total amount with VAT :"<<amount<<endl;
	file1<<"-------------------------------------------------------------"<<endl;
	file1.close();
	cout<<"\nTotal:";
	cout<<"\n------------------------------------------------------------------------------";
	cout<<"\n\tQuantity= "<<qtyt<<"\t\t Sum= "<<sumt<<"\tWith Vat:"<<amount;
	cout<<"\n------------------------------------------------------------------------------";

	pay:

		cout<<"\n\n\t\t\t****PAYMENT SUMMARY****\n";
		cout<<"\n\t\t\tTotal cash given: ";
		cin>>cash;

		if(cash>=amount)
			cout<<"\n\t\t\tTotal cash repaid: "<<cash-amount<<'\n';

		else
		{	cout<<"\n\t\t\tCash given is less than total amount!!!";

		goto pay;
		}

}

int bill::checkcustomer(char cus_id[5])
{
	fstream app;
	customer c;
	app.open("record_customer.txt",ios::in);
	while(!app.eof())
	{
		app.getline(c.ind,5,'|');
		app.getline(c.customer_ID,5,'|');
		app.getline(c.customer_name,15,'|');
		app.getline(c.manu_date,15,'|');
		app.getline(c.Company,15,'|');
		app.getline(c.address,15,'\n');

		if(strcmp(c.customer_ID,cus_id)==0)
		{
			cout<<"The customer name is : \n"<<c.customer_name;
			return 1;
			
		}
	}
}

void bill_module()
{
	medicine m;
	customer c;
     bill b;
	char  ch;
    int opt;
	int a=1;
	ifstream fin;
	int n;
	for(;;)
	{
		m.display_medicine();
		cout<<"\n\n\n";

	 	cout<<"\n\t\t\t\t\t\t\t==============================";
	 	cout<<"\n\t\t\t\t\t\t\tPharmacy Billing System";
	 	cout<<"\n\t\t\t\t\t\t\t==============================";
	 	cout<<"\n\t\t\t\t\t\t\t1.Add new bill";
	 	cout<<"\n\t\t\t\t\t\t\t2.Display previous bills";
	 	cout<<"\n\t\t\t\t\t\t\t3.Return to main page";
	 	cout<<"\n\t\t\t\t\t\t\tEnter the choice\t:";
	 cin>>opt;
	 switch(opt)
	 {
	 case 1:
	 	c.display_customer();
	 	cout<<"\n\n\n\n";
		b.billcalcu();
		b.billgene();
         break;
		
	 case 2:

		 fin.open("pracbill.txt", ios::in);
		 while(fin.get(ch))
		 {
			 cout<<ch;
		 }
		 fin.close();
         break;

		
	 case 3:
		return;
	 default:
		 cout<<"\a";
	 }
	}
}

void order_module()
{	stock d;
	order m;
	int choice;

	for(;;)
	{
		d.display_stock();
		cout<<"\n\n\n";
		cout<<"\t\t\t\t\t\t\t======================\n";
		cout<<"\t\t\t\t\t\t\t   Order MANAGEMENT\n";
		cout<<"\t\t\t\t\t\t\t======================\n";
		cout<<"\n\t\t\t\t\t\t\t1:Add order\n";
		cout<<"\t\t\t\t\t\t\t2:Search order\n";
		cout<<"\t\t\t\t\t\t\t3:Delete order\n";
		cout<<"\t\t\t\t\t\t\t4:Display order\n";
		cout<<"\t\t\t\t\t\t\t5:Modify order\n";
		cout<<"\t\t\t\t\t\t\t6: Return to main menu\n\n";
		cout<<"\t\t\t\t\t\t\tEnter the choice\n";
	
		cin>>choice;
		switch(choice)
		{
			case 1: m.add_order(); break;
			case 2: m.search_order(); break;
			case 3: m.delete_order(); break;
			case 4: m.display_order();break;
			case 5: m.modify_order();break;
			case 6: return;
			default:
			cout<<"\nInvalid choice !\n"; exit(0);	
		}
	}
}


void mainpage()
{
int choice;
stock d;
order o;
medicine m;
	for(;;)
	{
		
        cout<<"\n";
		cout<<"\t\t\t\t\t\t\t========================================\n";
		cout<<"\t\t\t\t\t\t\tWelcome to Pharmacy Management System\n";
		cout<<"\t\t\t\t\t\t\t========================================\n";
		cout<<"\n\t\t\t\t\t\t\t1:Medicine Module\n";
		cout<<"\t\t\t\t\t\t\t2:Customer Module\n";
		cout<<"\t\t\t\t\t\t\t3:Billing Module\n";
		cout<<"\t\t\t\t\t\t\t4:View Agency Stocks\n";
		cout<<"\t\t\t\t\t\t\t5:Add Orders\n";
		cout<<"\t\t\t\t\t\t\t6:Order Display\n";
        cout<<"\t\t\t\t\t\t\t7: Exit\n\n";
		cout<<"\t\t\t\t\t\t\tEnter the choice\n";
		cin>>choice;
		switch(choice)
		{
			case 1:medicine_module(); break;
			case 2:customer_module(); break;
			case 3:bill_module();break;
			case 4:d.display_stock();break;
		    case 5:order_module();break;
			case 6:o.display_order();break;
			case 7:exit(0);
			default:
			cout<<"\nInvalid choice !\n"; exit(0);	
		}
	}
}
void dealer_login()
{
	
	char  id[10];
    int ch;
    int pass;
    cout<<"\n\n\n\n";
    cout<<"\t\t\t\t\t\t==============================================\n";
    cout<<"\t\t\t\t\t\t||  Welcome to Pharmacy Management System    ||\n";
    cout<<"\t\t\t\t\t\t==============================================\n";
    cout<<"\n\n\n\n";
    cout<<"\t\t\t\t\t\t\t==========================\n";
    cout<<"\t\t\t\t\t\t\t||  DELEAR LOGIN PAGE    ||\n";
    cout<<"\t\t\t\t\t\t\t==========================\n";
    cout<<"\n\t\t\t\t\t\t\tEnter the Delear ID :";
    cin>>id;
    cout<<"\n\t\t\t\t\t\t\tEnter the Password :";
    cin>>pass;
    if((!strcmp(id,"dealer")) && pass==1234)
    {
        cout<<"\n\t\t\t\t\t\t\tlogin successfull\n\n\n";
        stock_module();
    }
    else
    {
        cout<<"\n\t\t\t\t\t\tInvalid password or userID";
        
    }
}

int admin_login()
{
	char  id[10];
    
    int pass;
    cout<<"\n\n\n\n";
    cout<<"\t\t\t\t\t\t\t==========================\n";
    cout<<"\t\t\t\t\t\t\t||  ADMIN LOGIN PAGE    ||\n";
    cout<<"\t\t\t\t\t\t\t==========================\n";
	login:
    cout<<"\n\t\t\t\t\t\t\tEnter the Admin ID :";
    cin>>id;
    cout<<"\n\t\t\t\t\t\t\tEnter the Password :";
    cin>>pass;
    if((!strcmp(id,"admin")) && pass==1234)
    {
        cout<<"\n\t\t\t\t\t\t\tlogin successfull\n\n\n";
        mainpage();
    }
    else
    {
        cout<<"\n\t\t\t\t\t\tInvalid password or userID\n\n\n";
        goto login;
    }
}
int main()
{
    
    int ch;
    
    cout<<"\n\n\n\n";
    cout<<"\t\t\t\t\t\t==============================================\n";
    cout<<"\t\t\t\t\t\t||  Welcome to Pharmacy Management System    ||\n";
    cout<<"\t\t\t\t\t\t==============================================\n";
    cout<<"\n\n\n\n";
    cout<<"\t\t\t\t\t\t\t==========================\n";
    cout<<"\t\t\t\t\t\t\t|| 1. ADMIN LOGIN PAGE   ||\n";
    cout<<"\t\t\t\t\t\t\t==========================\n";
	cout<<"\t\t\t\t\t\t\t==========================\n";
    cout<<"\t\t\t\t\t\t\t|| 2. DELEAR LOGIN PAGE  ||\n";
    cout<<"\t\t\t\t\t\t\t==========================\n";
    cout<<"\n\t\t\t\t\t\t\tEnter your choice for login :";
    cin>>ch;
	switch(ch)
	{
		case 1: admin_login(); break;
		case 2: dealer_login(); break;
	}
}   