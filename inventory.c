#include <stdio.h>
#include <string.h>
#define MAX 100
struct Product{
    int id;
    char name[30];
    float price;
    int qty;
};
struct Product p[MAX];
int n=0;
void add(){
    if(n>=MAX){printf("Inventory Full\n");return;}
    printf("ID: "); scanf("%d",&p[n].id);
    printf("Name: "); scanf("%29s",p[n].name);
    printf("Price: "); scanf("%f",&p[n].price);
    printf("Quantity: "); scanf("%d",&p[n].qty);
    n++;
}
void view(){
    int i;
    printf("\nID\tName\tPrice\tQty\n");
    for(i=0;i<n;i++)
        printf("%d\t%s\t%.2f\t%d\n",p[i].id,p[i].name,p[i].price,p[i].qty);
}
int find(int id){
    int i;
    for(i=0;i<n;i++) if(p[i].id==id) return i;
    return -1;
}
void search(){
    int id,i;
    printf("Enter ID: "); scanf("%d",&id);
    i=find(id);
    if(i==-1) printf("Not found\n");
    else printf("%d %s %.2f %d\n",p[i].id,p[i].name,p[i].price,p[i].qty);
}
void sell(){
    int id,q,i;
    float bill;
    printf("Enter ID: "); scanf("%d",&id);
    i=find(id);
    if(i==-1){printf("Not found\n");return;}
    printf("Quantity: "); scanf("%d",&q);
    if(q>p[i].qty){printf("Insufficient stock\n");return;}
    p[i].qty-=q;
    bill=q*p[i].price;
    printf("Bill = %.2f\nRemaining = %d\n",bill,p[i].qty);
}
void restock(){
    int id,q,i;
    printf("Enter ID: "); scanf("%d",&id);
    i=find(id);
    if(i==-1){printf("Not found\n");return;}
    printf("Add Quantity: "); scanf("%d",&q);
    p[i].qty+=q;
}
void del(){
    int id,i,j;
    printf("Enter ID: "); scanf("%d",&id);
    i=find(id);
    if(i==-1){printf("Not found\n");return;}
    for(j=i;j<n-1;j++) p[j]=p[j+1];
    n--;
}
void low(){
    int i,f=0;
    printf("Low Stock (<10)\n");
    for(i=0;i<n;i++){
        if(p[i].qty<10){
            printf("%d %s Qty:%d\n",p[i].id,p[i].name,p[i].qty);
            f=1;
        }
    }
    if(!f) printf("No low stock items\n");
}
void save(){
    FILE *fp=fopen("inventory.txt","wb");
    if(!fp) return;
    fwrite(&n,sizeof(int),1,fp);
    fwrite(p,sizeof(struct Product),n,fp);
    fclose(fp);
}
void load(){
    FILE *fp=fopen("inventory.txt","rb");
    if(!fp) return;
    fread(&n,sizeof(int),1,fp);
    fread(p,sizeof(struct Product),n,fp);
    fclose(fp);
}
int main(){
    int ch;
    load();
    while(1){
        printf("\n1.Add\n2.View\n3.Search\n4.Sell\n5.Restock\n6.Delete\n7.Low Stock\n8.Save & Exit\nChoice: ");
        scanf("%d",&ch);
        switch(ch){
            case 1:add();break;
            case 2:view();break;
            case 3:search();break;
            case 4:sell();break;
            case 5:restock();break;
            case 6:del();break;
            case 7:low();break;
            case 8:save();printf("Saved.\n");return 0;
            default:printf("Invalid choice\n");
        }
    }
}
