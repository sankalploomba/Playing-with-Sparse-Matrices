#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

struct node
{
	int value;
	node* right;
	node* down;
};

node* head=new node;
node* row=new node;
node* column=new node;


int main()
{
    fstream f1,f2;
    int i,j,j1,j2,k,nor1=0,nor2=0,noc1=0,noc2=0,sum1=0,sum2=0,val1=0,val2=0;          //nor= no. of rows, noc= no. of columns
    string a1; string a2;

    f1.open("file1.csv");

        if(f1.is_open())
        {
            while(getline(f1,a1))
            {
                cout<<endl<<a1<<"\t";
                noc1=0;
                for(i=0;a1[i]!='\0';i++)
                {
                    if(a1[i]==',')
                    noc1++;
                }
                nor1++;
            }
            noc1++;

        cout<<"nor1= "<<nor1<<"\tnoc1= "<<noc1<<endl;
        f1.close();
        }

		else
        {
            cout<<"Unable to open file."<<endl;
            exit(-1);
        }


    f2.open("file1.csv");

        if(f2.is_open())
        {
            while(getline(f2,a2))
            {
                cout<<endl<<a2<<"\t";
                noc2=0;
                for(i=0;a2[i]!='\0';i++)
                {
                    if(a2[i]==',')
                    noc2++;
                }
                nor2++;
            }
            noc2++;

        cout<<"nor2= "<<nor2<<"\tnoc2= "<<noc2<<endl;
        f2.close();
        }

		else
        {
            cout<<"Unable to open file."<<endl;
            exit(-1);
        }
		
		if((nor1!=nor2)&&(noc1!=noc2))
		{
			cout<<"Unable to open file."<<endl;
            exit(-1);
		}
		
		head->right=column;
		head->down=row;

		bool column_first=true, row_first=true, same_column=false, same_row=false, empty_row=false;

		f1.open("file1.csv");
		f2.open("file2.csv");
		
		for(i=0;i<nor1;i++)
		{
			same_column=false, same_row=false, empty_row=false;
            //cout<<endl<<"---------------------------"<<endl;
			//cout<<"test out."<<endl;

				getline(f1,a1);
				getline(f2,a2);
				string sub1,sub2;
				
				val1=0; j1=(-1);
                sum1=0; val2=0; j2=(-1); sum2=0;
				
				for(k=0; a1[k]!='\0'; k++)
				{
				    val1=0;
				    //cout<<"test in. "<<endl;
					if(a1[k]==',')
					{
						//cout<<"k (if): "<<endl;
						//val=0;

						stringstream StoI(sub1);
						StoI >> val1;                                //putting values from string to integer val
						//cout<<"val: "<<val<<endl;
						sub1="";
						j++;
					}
					else if(a1[k+1]=='\0')
					{
						//cout<<"k (else if): "<<endl;
						sub+=a[k];
						//val=0;
						stringstream StoI(sub);
						StoI >> val;                                //putting values from string to integer val
						//cout<<"val: "<<val<<endl;
						sub="";
						j++;
					}
					else
					{
						//cout<<"k (else): "<<endl;
						sub+=a[k];
					}

                    //cout<<"test in. : a "<<a<<endl;
                    //cout<<"j : "<<j<<endl;

                    if(val!=0)
                    {
                        //cout<<"test in if."<<endl;

                        node *p=new node;
                        p->value = val;
                        p->down=NULL;
                        p->right=NULL;

                        if(row_first==true)
                        {
                            row_first=false;
                            //cout<<"r 1st."<<endl;                 //first row is being made here
                            row->value=i;
                            row->down=NULL;
                            row->right=p;
                            row=p;
                        }
                        else
                        {
                            node* r=new node;
                            r=head->down;
                            //cout<<"r subsequent."<<endl;          //now, once first row has been created.... subsequent values are checked in this.
                            while(r!=NULL)
                            {
                                //cout<<"test while r."<<endl;
                                if(i==r->value)
                                {
                                    //cout<<"test while r if"<<endl;
                                    row->right=p;
                                    row=p;
                                    same_row=true;
                                    break;
                                }

                                else
                                {
                                    //cout<<"test while r else"<<endl;
                                    r=r->down;
                                }

                            }
                            if(same_row==false)
                            {
                                //cout<<"not same row. old row header= "<<row->value<<endl;
                                row->value=i;
                                //cout<<"row header value: "<<row->value<<endl;
                                row->down=NULL;
                                row->right=p;
                                row=p;
                                //cout<<"p= "<<row->value<<endl;
                            }

                        }


                        if(column_first==true)                          //first column is being made here
                        {
                            column_first=false;
                            //cout<<"c 1st."<<endl;
                            column->value=j;
                            column->down=p;
                            column->right=NULL;
                            column=p;
                        }
                        else
                        {
                            node* c=new node;
                            c=head->right;
                            //cout<<"c subsequent."<<endl;         //now, once first column has been created.... subsequent values are checked in this.
                            while(c!=NULL)
                            {
                                //cout<<"test while c."<<endl;
                                if(j==c->value)
                                {
                                    //cout<<"test while c if"<<endl;
                                    column=head->right;

                                    while(column->value!=j)
                                        column=column->right;

                                    if(column->down==NULL)
                                        column->down=p;

                                    else
                                    {
                                        while(column->down!=NULL)
                                            column=column->down;
                                        column->down=p;
                                    }
                                    column=p;
                                    same_column=true;
                                    break;
                                }

                                else
                                {
                                    //cout<<"test while c else."<<endl;
                                    c=c->right;
                                }
                            }

                            if(same_column==false)
                            {
                                //cout<<"not any of the column."<<endl;
                                column = head->right;
                                while(column->right!=NULL)
                                {
                                    //cout<<"check col"<<endl;
                                    column=column->right;
                                }
                                node* a=new node;                       //Creating new column headers.
                                a->value=j;
                                a->down=NULL;
                                a->right=NULL;

                                column->right=a;
                                column=a;
                                column->down=p;
                                column=p;
                            }

                        }

                    }



                    //cout<<endl<<"end of inner loop: "<<row->value<<endl;
                    sum+=val;       //sum variable calculates the sum of a row.

                }               //inner loop ends

                //cout<<"sum= "<<sum<<endl;
                if(sum==0)
                    empty_row=true;

                if(row_first==false && empty_row==false)
                {
                    //cout<<"Creating new row header. "<<endl;          //Creating new row header here.
                    row=head->down;
                    while(row->down!=NULL)
                    {
                        //cout<<"check row"<<endl;
                        row=row->down;
                    }

                    node* t=new node;
                    t->down=NULL;
                    t->right=NULL;
                    row->down=t;
                    row=t;
                }
                //cout<<endl<<"end of outer loop: : "<<row->value<<endl;

        }   //outer loop ends

		delete row;


		cout<<endl;


		row=head->down;
		while(row->down!=NULL)                              //displays row headers created
		{
			cout<<"row value: "<<row->value<<"\t";
			row=row->down;
		}
		cout<<endl;

		column=head->right;
		while(column!=NULL)                                 //displays column headers created
		{
			cout<<"col value: "<<column->value<<"\t";
			column=column->right;
		}


        int x=0;
        row=head->down;
		column=head->right;

		cout<<endl<<endl;
		for(i=0;i<nor;i++)                                              //DISPLAY
		{
			if(row->down!=NULL && i==row->value)
			{
				//cout<<endl<<"row no: "<<row->value<<endl;

					for(j=0;j<noc;j++)
					{
						bool output=false;

							column=head->right;
							while(column!=NULL)
							{
								//cout<<"while o/p. j: "<<j<<"\t column->value: "<<column->value<<"\t column->down->value: "<<column->down->value<<"\t row->right->value: "<<row->right->value<<endl;
								if((j==column->value) && (column->down==row->right))
								{
									//cout<<"if: ";
									cout<<row->right->value<<"\t";
									row=row->right;
									if(column->down->down!=NULL)
										column->down=column->down->down;
									output=true;
									break;
								}

								else
								{
									column=column->right;
								}
							}

						if(output==false)               //runs when the one element of row is 0
						{
							//cout<<"else: ";
							cout<<"0\t";
						}
						//cout<<endl;
					}




				cout<<endl;

				row=head->down;
				//cout<<"x: "<<x<<" i: "<<i<<endl;
				for(int k=0;k<=(i-x);k++)
					row=row->down;

			}
			else                                    //runs when the whole row is 0
			{
				x++;
				//cout<<"from else: ";
				for(int y=0;y<noc;y++)
					cout<<"0\t";

				cout<<endl;
			}

		fin.close();
    }
return 0;
}
