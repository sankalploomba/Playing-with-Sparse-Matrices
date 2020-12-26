#include<iostream>
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
	int i,j,size;
	cout<<"Enter size: ";
	cin>>size;

	int a[size][size];
	cout<<"Enter array: "<<endl;

	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			cin>>a[i][j];

head->value=NULL;
head->right=column;
head->down=row;

bool column_first=true, row_first=true, same_column=false, same_row=false, empty_row=false;

for(i=0;i<size;i++)
{
    same_column=false, same_row=false, empty_row=false;

    //cout<<"\ntest out."<<endl;

	for(j=0;j<size;j++)
	{
	    //cout<<"test in."<<endl;

        if(a[i][j]!=0)
		{
		    //cout<<"test in if."<<endl;

			node *p=new node;
			p->value=a[i][j];
			p->down=NULL;
			p->right=NULL;

            if(row_first==true)
            {
                row_first=false;
                //cout<<"r 1st."<<endl;
                row->value=i;
                row->down=NULL;
                row->right=p;
                row=p;
            }
            else
            {
                node* r=new node;
                r=head->down;
                //cout<<"r subsequent."<<endl;
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
                    //cout<<"not same row."<<row->value<<endl;
                    row->value=i;
                    //cout<<row->value<<endl;
                    row->down=NULL;
                    row->right=p;
                    row=p;
                    //cout<<row->value<<endl;
                }

            }


            if(column_first==true)
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
                //cout<<"c subsequent."<<endl;
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
                    node* a=new node;
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

	}

	//cout<<endl<<row->value<<endl;
	int sum=0;
	for(int m=0;m<size;m++)
        sum+=a[i][m];

	if(sum==0)
        empty_row=true;

	if(row_first==false && empty_row==false)
    {
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
    //cout<<endl<<row->value<<endl;
}

delete row;


cout<<endl;


row=head->down;
while(row->down!=NULL)
{
    cout<<"row value: "<<row->value<<"\t";
    row=row->down;
}
cout<<endl;
column=head->right;
while(column!=NULL)
{
    cout<<"column value: "<<column->value<<"\t";
    column=column->right;
}



row=head->down;
column=head->right;

int x=0;

cout<<endl<<endl;
for(i=0;i<size;i++)
{
    if(row->down!=NULL && i==row->value)
    {
        //cout<<endl<<"row no: "<<row->value<<endl;

            for(j=0;j<size;j++)
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

                if(output==false)
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
    else
    {
        x++;
        //cout<<"from else: ";
        for(int y=0;y<size;y++)
            cout<<"0\t";

        cout<<endl;
    }


}
return 0;
}
