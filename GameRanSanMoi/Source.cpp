#include<iostream>
#include "ThuVienCuaThuanCPP.h"
using namespace std;
#define MAX 1000

int toa_dox[MAX] = { 0 };//tọa độ x của rắn
int toa_doy[MAX] = { 0 };//tọa độ y của rắn
int sl = 3;//size của rắn 
int xqua = -1;//tọa độ x của quả
int yqua = -1;//tọa độ y của quả 
int cnt = 1;//tạo rắn 7 sắc cầu vồng 

void ve_tuong();
void khoi_tao_ran();
void ve_ran();
void di_chuyen_ran(int x, int y);
void play();
bool gameOver();
void tao_qua();
void in_qua();
bool kiem_tra_ran_an_qua();
void xu_ly_ran_an_qua();
bool kiem_tra_ran_de_qua();
bool kiem_tra_ran_cham_than();

void ve_tuong() {
	SetColor(2);
	//vẽ 2 hàng trên và dưới 
	for (int x = 10; x <= 100; x++) {
		gotoXY(x, 1); cout << char(196);
		gotoXY(x, 25); cout <<char(196);
	}
	//vẽ 2 cột 
	for (int y = 1; y <= 25; y++) {
		gotoXY(10, y); cout <<char(179);
		gotoXY(100, y); cout <<char(179);
	}
	//vẽ 4 góc 
	gotoXY(10, 1); cout << char(218);
	gotoXY(100, 1); cout << char(191);
	gotoXY(10, 25); cout << char(192);
	gotoXY(100, 25); cout << char(217);
	SetColor(7);
}

//khởi tạo các tọa độ của con rắn 
void khoi_tao_ran() {
	int x_khoiTao = 40;//tọa độ x của cái Đầu của con rắn
	int y_khoiTao = 12;//tọa độ y của cái Đầu con rắn 
	for (int i = 0; i < sl; i++) {
		toa_dox[i] = x_khoiTao;//khởi tạo các giá trị cùng hàng y nhưng x giảm dần 
		x_khoiTao--;
		toa_doy[i] = y_khoiTao;
	}
}

//từ các tọa độ đã được khởi tạo ta gotoXY đến và vẽ 
void ve_ran() {
	SetColor(cnt++);
	if (cnt == 16) cnt = 1;
	for (int i = 0; i < sl; i++) {
		gotoXY(toa_dox[i], toa_doy[i]);
		if (i == 0) cout << "@";//vẽ đầu con rắn 
		else cout << "o";//vẽ thân con rắn 
	}
	SetColor(7);//trả lại màu giống hệ thống 
}

//dùng thuật toán thêm 1 phần tử vào mảng để di chuyển rắn 
void di_chuyen_ran(int x, int y) {
	for (int i = sl; i > 0; i--) {
		toa_dox[i] = toa_dox[i - 1];
		toa_doy[i] = toa_doy[i - 1];
	}
	toa_dox[0] = x;
	toa_doy[0] = y;
}

void play() {
	ShowCur(0);
	ve_tuong();
	khoi_tao_ran();

	tao_qua();
	in_qua();

	int x = toa_dox[0];
	int y = toa_doy[0];

	int check = 2;//check=0 di xuong, 1 di len, 2 sang phai, 3 sang trai
	while (true) {
		//xóa những phần đuôi thừa của con rắn 
		gotoXY(toa_dox[sl], toa_doy[sl]); cout << " ";
		ve_ran();

		//đọc dữ liêu jtuwf người dùng nhập vào 
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {//chắc chắn người dùng nhập mũi tên
				c = _getch();//đọc tiếp 1 lần nữa 
				if (c == 72 && check != 0) check = 1;
				else if (c == 80 && check != 1) check = 0;
				else if (c == 77 && check != 3) check = 2;
				else if (c == 75 && check != 2) check = 3;
			}
		}

		//khởi tạo các tính năng đi xuống/lên/sang trái/sang phải.
		if (check == 0) y++;
		else if (check == 1) y--;
		else if (check == 2) x++;
		else if (check == 3) x--;

		if (gameOver()) {
			system("cls");
			gotoXY(50, 13);
			cout << "GAME OVER";
			break;
		}

		xu_ly_ran_an_qua();

		gotoXY(1,1); cout <<"Diem: "<<sl;
		di_chuyen_ran(x, y);
		Sleep(80);
	}
}

//kết thúc game nếu rắn chạm biên hoặc tự cắn vào thân mình 
bool gameOver() {
	if (toa_dox[0] == 10 || toa_dox[0] == 100 || toa_doy[0] == 1 || toa_doy[0] == 25) return true;
	if (kiem_tra_ran_cham_than()) return true;
	return false;
}

//tạo tọa độ quả 1 cách ngẫu nhiên bằng hàm rand()
void tao_qua() {
	do {
		xqua = rand() % (99 - 11 + 1) + 11;
		yqua = rand() % (24 - 2 + 1) + 2;
	} while (kiem_tra_ran_de_qua());
}

//vẽ cái quả để cho con rắn ăn 
void in_qua() {
	SetColor(4);
	gotoXY(xqua, yqua);
	cout << char(3);
	SetColor(7);
}

//kiểm tra xem con rắn đã ăn quả hay chưa 
bool kiem_tra_ran_an_qua() {
	return (toa_dox[0] == xqua && toa_doy[0] == yqua);
}

//nếu con rắn ăn quả thì tăng số lượng và tạo quả mới 
void xu_ly_ran_an_qua() {
	if (kiem_tra_ran_an_qua()) {
		++sl;//tăng size của con rắn 
		//tạo thêm quả mới 
		tao_qua();
		in_qua();
	}
}

//tránh trường hợp quả đè lên con rắn 
bool kiem_tra_ran_de_qua() {
	for (int i = 0; i < sl; i++) {
		//tạo độ của con rắn không được trùng với tọa độ của quả 
		if (xqua == toa_dox[i] && yqua == toa_doy[i]) return true;
	}
	return false;
}

//nếu rắn cắt vào thân thì END GAME 
bool kiem_tra_ran_cham_than() {
	for (int i = 1; i <= sl; i++) {
		//tọa độ đầu trùng với các tọa độ còn lại của con rắn 
		if (toa_dox[0] == toa_dox[i] && toa_doy[0] == toa_doy[i]) return true;
	}
	return false;
}

void main() {
	play();
	_getch();
}