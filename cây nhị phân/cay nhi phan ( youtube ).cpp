#include <iostream>
#include <queue>
#include <stack>
using namespace std;
// khai báo cấu trúc  1 cái node
struct node
{
    int data; // dữ liệu của node ==> dữ liệu mà node sẽ lưu trữ
    struct node* pLeft; // node liên kết bên trái của cây <=> cây con trái
    struct node* pRight; // node liên kết bên phải của cây <=> cây con phải
};
typedef struct node NODE;
typedef NODE* TREE;

// khởi tạo cây
void khoi_tao_cay(TREE& t)
{
    t = NULL; // cây rỗng
}

// hàm thêm phần tử x vào cây nhị phân
void ThemNodeVaoCay(TREE& t, int x)
{
    // nếu cây rỗng
    if (t == NULL)
    {
        NODE* p = new NODE; // khởi tạo 1 cái node để thêm vào cây
        p->data = x;// thêm dữ liệu x vào data
        p->pLeft = NULL;
        p->pRight = NULL;
        t = p;// node p chính là node gốc <=> x chính là node gốc
    }
    else // cây có tồn tại phần tử
    {
        // nếu phần tử thêm vào mà nhỏ hơn node gốc ==> thêm nó vào bên trái
        if (t->data > x)
        {
            ThemNodeVaoCay(t->pLeft, x); // duyệt qua trái để thêm phần tử x
        }
        else if (t->data < x) // nếu phần tử thêm vào mà lớn hơn node gốc ==> thêm nó vào bên phải
        {
            ThemNodeVaoCay(t->pRight, x); // duyệt qua phải để thêm phần tử x
        }
    }
}
NODE* create_node(int x)
{
    NODE* p = new NODE;
    if (p == NULL)
    {
        cout << "khong du bo nho de cap phat ";
        return NULL;
    }
    p->data = x;
    p->pLeft = NULL;
    p->pRight = NULL;
    return p;
}
// hàm xuất cây nhị phân theo NLR
void Duyet_NLR(TREE t)
{
    // nếu cây còn phần tử thì tiếp tục duyệt
    if (t != NULL)
    {
        cout << t->data << " "; // xuất dữ liệu trong node
        Duyet_NLR(t->pLeft); // duyệt qua trái
        Duyet_NLR(t->pRight); // duyệt qua phải
    }
}

// hàm xuất cây nhị phân theo NRL
void Duyet_NRL(TREE t)
{
    // nếu cây còn phần tử thì tiếp tục duyệt
    if (t != NULL)
    {
        cout << t->data << " "; // xuất dữ liệu trong node
        Duyet_NRL(t->pRight); // duyệt qua phải 
        Duyet_NRL(t->pLeft); // duyệt qua trái
    }
}

// hàm xuất cây nhị phân theo LNR <=> xuất ra các phần tử từ bé đến lớn
void Duyet_LNR(TREE t)
{
    // nếu cây còn phần tử thì tiếp tục duyệt
    if (t != NULL)
    {
        Duyet_LNR(t->pLeft); // duyệt qua trái
        cout << t->data << "  "; // xuất giá trị của node
        Duyet_LNR(t->pRight); // duyệt qua phải
    }
}

// hàm xuất cây nhị phân theo RNL <=> xuất ra các phần tử từ lớn đến bé
void Duyet_RNL(TREE t)
{
    // nếu cây còn phần tử thì tiếp tục duyệt
    if (t != NULL)
    {
        Duyet_RNL(t->pRight); // duyệt qua phải
        cout << t->data << "  "; // xuất giá trị của node
        Duyet_RNL(t->pLeft); // duyệt qua phải
    }
}

// hàm xuất cây nhị phân theo LRN
void Duyet_LRN(TREE t)
{
    // nếu cây còn phần tử thì tiếp tục duyệt
    if (t != NULL)
    {
        Duyet_LRN(t->pLeft); // duyệt qua trái
        Duyet_LRN(t->pRight); // duyệt qua phải
        cout << t->data << "  "; // xuất giá trị của node
    }
}

// hàm xuất cây nhị phân theo RLN
void Duyet_RLN(TREE t)
{
    // nếu cây còn phần tử thì tiếp tục duyệt
    if (t != NULL)
    {
        Duyet_RLN(t->pRight); // duyệt qua phải
        Duyet_RLN(t->pLeft); // duyệt qua trái
        cout << t->data << "  "; // xuất giá trị của node
    }
}
bool kiem_tra_ng_to(int x)
{
    if (x < 2)
    {
        return false;
    }
    else
    {
        if (x == 2)
        {
            return true;
        }
        else
        {
            if (x % 2 == 0)
            {
                return false;
            }
            else
            {
                for (int i = 2; i < x; i++)
                {
                    if (x % i == 0)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
void dem_ng_to(TREE t, int& dem) //ham dem so ng to 
{
    if (t != NULL)
    {
        if (kiem_tra_ng_to(t->data) == true)
        {
            dem++;
        }
        dem_ng_to(t->pLeft, dem);
        dem_ng_to(t->pRight, dem);
    }
}int tong_ng_to(TREE t) //ham tinh tong so ng to 
{
    int tong = 0;
    if (!t)
    {
        return 0;
    }
    if (kiem_tra_ng_to(t->data));
    {
        tong += t->data;
    }
    tong += tong_ng_to(t->pLeft);
    tong += tong_ng_to(t->pRight);
    return tong;
}
void node_hai_con(TREE t)
{
    if (t != NULL)
    {
        if (t->pLeft != NULL && t->pRight != NULL)
        {
            cout << t->data << "";
        }
        node_hai_con(t->pLeft); //duyệt sang cây con trái của node hiện tại
        node_hai_con(t->pRight); //duyệt sang cây con phải của node hiện tại
    }
}

void node_mot_con(TREE t)
{
    if (t != NULL)
    {
        if (t->pLeft != NULL && t->pRight != NULL || t->pLeft == NULL && t->pRight != NULL)
        {
            cout << t->data << " ";
        }
        node_mot_con(t->pLeft); //duyệt sang cây con trái của node hiện tại
        node_mot_con(t->pRight); // //duyệt sang cây con phải của node hiện tại
    }
}
void node_la(TREE t)
{
    if (t != NULL)
    {
        if (t->pLeft == NULL && t->pLeft == NULL)
        {
            cout << t->data << " ";
        }
        node_la(t->pLeft);
        node_la(t->pRight);
    }
}
int dem_node(TREE t)
{
    int dem = 0;
    if (!t)
    {
        return 0;
    }
    dem++;
    dem += dem_node(t->pLeft);
    dem += dem_node(t->pRight);
    return dem;
}
int tong_node(TREE t)
{
    int tong = 0;
    if (!t)
    {
        return 0;
    }
    tong += t->data;
    tong += tong_node(t->pLeft);
    tong += tong_node(t->pRight);
    return tong;
}
int chieu_cao(TREE t)
{
    int hLeft, hRight;
    if (!t)
    {
        return 0;
    }
    hLeft = chieu_cao(t->pLeft);
    hRight = chieu_cao(t->pRight);
    if (hLeft > hRight)
    {
        return hLeft + 1; //+1 la cong nut goc cua cay
    }
    else
    {
        return hRight + 1;
    }
}
void xoa_cay(TREE t)
{
    if (!t)
    {
        return;
    }
    xoa_cay(t->pLeft);
    xoa_cay(t->pRight);
    delete t;
}
int tim_max(TREE t)
{
    int maxLeft, maxRight, max;
    if (!t->pLeft && !t->pRight)
    {
        return t->data;
    }
    maxLeft = tim_max(t->pLeft);
    maxRight = tim_max(t->pLeft);
    max = t->data;
    max = max > maxLeft ? max : maxLeft;
    max = max > maxRight ? max : maxRight;
    return max;
}
NODE* search(NODE* t) //tim ptu max tren cay nhi phan tim kiem
{
    if (!t)
    {
        return NULL;
    }
    if (t->data < 0)
    {
        return t;
    }
    search(t->pLeft);
    search(t->pRight);
}
NODE* max_am(NODE* t)//tim ptu max am tren cay nhi phan thuong
{
    if (!t)
    {
        return NULL;
    }
    if (t->data < 0)
    {
        return t;
    }
    NODE* p = max_am(t->pLeft);
    if (!t)
    {
        return max_am(t->pRight);
    }
}
int tinh_tongk(NODE *t, int k)
{
    int tong = 0;
    if (!t)
        return 0;
    if (k == 0)
    {
        tong += t->data;
    }
    k--;
    tong += tinh_tongk(t->pLeft, k);
    tong += tinh_tongk(t->pRight, k);
    return tong;
}
int dem_chan(TREE t)
{
    int dem = 0;
    if (!t)
    {
        return 0;
    }
    if (t->data % 2 == 0)
    {
        dem++;
    }
    dem += dem_chan(t->pLeft);
    dem += dem_chan(t->pRight);
    return dem;
}
void be_rong_NLR(NODE* t)
{
    if (t == NULL)
    {
        return;
    }
    queue<NODE*>q;
    q.push(t);
    while (!q.empty())
    {
        NODE* p;
        p = q.front(); //nhap gia tri tren cung
        q.pop(); //xoa gia tri tren cung
        cout << p->data<<" ";
        if (p->pLeft != NULL)
        {
            q.push(p->pLeft);
        }
        if (p->pRight != NULL)
        {
            q.push(p->pRight);
        }
    }
}
void chieu_sau_NLR(NODE* t)
{
    stack<NODE*>q;
    NODE* p;
    q.push(t);
    while (!q.empty())
    {
        p = q.top();
        q.pop();
        cout << p->data << " ";
        if (p->pRight != NULL)
        {
            q.push(p->pRight);
        }
        if (p->pLeft != NULL)
        {
            q.push(p->pLeft);
        }
    }
}
NODE* tim_node(NODE* t, int x)
{
    if (t == NULL)
    {
        return NULL;
    }
    if (t->data == x)
    {
        return t;
    }
    else if (t->data > x)
    {
        return tim_node(t->pLeft, x);
    }
    else
    {
        return tim_node(t->pRight, x);
    }
}
NODE* tim_the_mang(NODE* &p)
{
    //ham tim nut q the mang cho nut p, f la nut cha cua nut q
    NODE* f = p, * q = p->pRight;
    while (q->pLeft != NULL)
    {
        f = q; //luu nut cha cua q
        q = q->pLeft; //q qua ben trai
    }
    p->data = q->data; //tim dc ptu the mang cho p va q
    if (f == p) //neu cha cua q la p
    {
        f->pRight = q->pRight;
    }
    else
    {
        f->pLeft = q->pRight;
    }
    return q; //tra ve nut q la nut the mang cho p
}
int xoa_nut_x(NODE* &t, int x)
{
    if (t == NULL)
    {
        return 0;
    }
    if (t->data > x)
    {
        return xoa_nut_x(t->pLeft, x);
    }
    else if (t->data < x)
    {
        return xoa_nut_x(t->pRight, x);
    }
    else
    {
        NODE* p = t;
        if (t->pLeft == NULL) //khi cay con k co nhanh trai
        {
            t = t->pRight;
            delete p;
        }
        else if (t->pRight == NULL) //khi cay con k co nhanh phai 
        {
            t = t->pLeft;
            delete p;
        }
        else
        {
            NODE* q = tim_the_mang(p);
            delete q;
        }
        return 1;
    }
}
int dem_xy(NODE* t, int x, int y)
{
    int dem = 0;
    if (!t)
    {
        return 0;
    }
    if (t->data > x && t->data < y)
    {
        dem++;
    }
    dem += dem_xy(t->pLeft, x, y);
    dem += dem_xy(t->pRight, x, y);
    return dem;
}
//void insert_node(TREE t, NODE* p)
//{
//    if (p == NULL)
//        return; //Thực hiện không thành công
//    if (t == NULL) //Cây rỗng, nên thêm vào gốc
//    {
//        t = p;
//        return; //Thực hiện thành công
//    }
//    if (t->data == p->data)
//        return;
//    if (p->data < t->data)
//        insert_node(t->pLeft, p); //Them ben trái
//    else
//        insert_node(t->pRight, p);	 //Thực hiện thành công
//}
//void tao_cay_tu_mang(NODE* &t, int a[])
//{
//    int i, x,n = 5;
//    for (int i = 0; i < n; i++)
//    {
//        x = a[i];
//        insert_node(t, create_node(x));
//    }
//}
int main()
{
    TREE t;
    khoi_tao_cay(t);
    cout << " =========== MENU ===========" << endl;
    cout << "1. duyet cay NLR" << endl;
    cout << "2. duyet cay NRL" << endl;
    cout << "3. duyet cay LNR" << endl;
    cout << "4. duyet cay RNL" << endl;
    cout << "5. duyet cay LRN" << endl;
    cout << "6. duyet cay RLN" << endl;
    cout << "7. dem so nguyen to " << endl;
    cout << "8. node 1 con " << endl;
    cout << "9. node 2 con " << endl;
    cout << "10. node la " << endl;
    cout << "11. dem node " << endl;
    cout << "12. tinh tong node " << endl;
    cout << "13. chieu cao cua cay " << endl;
    cout << "14. xoa cay " << endl;
    cout << "15. tim ptu max tren cay " << endl;
    cout << "16. tong so ng to " << endl;
    cout << "17. duyet cay theo be rong " << endl;
    cout << "18. duyet cay theo chieu sau " << endl;
    cout << "19. dem so chan " << endl;
    cout << "20. tinh tong k " << endl;
    cout << "21. tao cay nhi phan tu mang " << endl;
    cout << "22. tim kiem nut co gtri x " << endl;
    cout << "23. xoa gtri x " << endl;
    cout << "24. dem x toi y " << endl;
    cout << endl;
    int ptu, chon;
    cout << "nhap so ptu : ";
    cin >> ptu;
    cout << "nhap so nguyen : ";
    for (int i = 0; i < ptu; i++)
    {
        int n;
        cin >> n;
        ThemNodeVaoCay(t, n);
    }
    cout << "nhap lua chon: ";
    cin >> chon;
    switch (chon)
    {
    case 1:
        cout << "duyet cay theo NLR : ";
        Duyet_NLR(t);
        break;                
    case 2:
        cout << "duyet cay theo NRL : ";
        Duyet_NRL(t);
        break;
    case 3:
        cout << "duyet cay theo LNR : ";
        Duyet_LNR(t);
        break;
    case 4:
        cout << "duyet cay theo RNL : ";
        Duyet_RNL(t);
        break;
    case 5:
        cout << "duyet cay theo LRN : ";
        Duyet_LRN(t);
        break;
    case 6:
        cout << "duyet cay theo RLN : ";
        Duyet_RLN(t);
        break;
    case 7:
    {
        int dem = 0;
        dem_ng_to(t, dem);
        cout << "so luong so nguyen to : " << dem;
        break;
    }
    case 8:
        cout << "node co 2 con : " << " ";
        node_mot_con(t);
        break;
    case 9:
        cout << "node co 1 con : " << " ";
        node_hai_con(t);
        break;
    case 10:
        cout << "node la : " << " ";
        node_la(t);
        break;
    case 11:
        cout << "so nut tren cay : "<<dem_node(t);
        break;
    case 12:
        cout << "tong so nut tren cay : " << tong_node(t);
        break;
    case 13: 
        cout << "chieu cao tren cay : " <<chieu_cao(t);
        break;
    case 14:  
        xoa_cay(t);
        break;
    case 15:
        cout << "max am tren cay : ";
        max_am(t);
        break;
    case 16: 
        cout << "tong so ng to : "<<tong_ng_to(t);
        break;
    case 17: 
        cout << "be rong : ";
        be_rong_NLR(t);
        break;
    case 18: 
        cout << "chieu sau : ";
        chieu_sau_NLR(t);
        break;
    case 19: 
        cout << "dem chan "<<dem_chan(t);
        break;
    case 20: 
        int k;
        cout << "nhap k : ";
        cin >> k;
        cout <<"ket qua "<< tinh_tongk(t, k);
        break;
   /* case 21: 
    {
    tao_cay_tu_mang(t, a);
    Duyet_LNR(t);
    break;
    }*/
    case 22: 
        int x;
        cout << "nhap so muon tim ";
        cin >> x;
        if (tim_node(t, x)!= NULL)
        {
            cout << "tim thay ";
        }
        else
        {
            cout << "khong tim thay ";
        }
        break;
    case 23:
        cout << "nhap nut can xoa: ";
        cin >> x;
        xoa_nut_x(t, x);
        cout << "duyet cay theo be rong NLR : "<<" ";
        be_rong_NLR(t);
        cout << endl;
        break;
    case 24: 
    {
    int x, y;
    cout << "nhap x : ";
    cin >> x;
    cout << "nhap y : ";
    cin >> y;
    cout<<dem_xy(t, x, y);
    break;
    }
    default: cout << "ban nhap sai cu phap. Vui long nhap lai";
        break;
    }
}