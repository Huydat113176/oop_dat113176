#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() {
    ma_xe = 0;
    loai_xe = "";
    gio_vao = 0;
    tg_do = 0;
}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg) {
    ma_xe = ma;
    loai_xe = loai;
    gio_vao = gio;
    tg_do = tg;
}

int phuong_tien::lay_ma_xe() const {
    return ma_xe;
}

string phuong_tien::lay_loai_xe() const {
    return loai_xe;
}

double phuong_tien::tinh_phi() const {
    double don_gia = 0;

    if (loai_xe == "Car")
        don_gia = 6000;
    else if (loai_xe == "Motorcycle")
        don_gia = 4000;
    else if (loai_xe == "Bicycle")
        don_gia = 2000;

    bool cao_diem =
        (gio_vao >= 6 && gio_vao < 10) ||
        (gio_vao >= 15 && gio_vao < 19);

    double he_so = cao_diem ? 1.3 : 0.95;

    double tong = 0;

    if (tg_do >= 1)
        tong += don_gia * he_so;

    if (tg_do >= 2)
        tong += don_gia * he_so;

    if (tg_do > 2)
        tong += (tg_do - 2) * don_gia * 0.9;

    return tong;
}

void phuong_tien::hien_thi() const {
    cout << left
         << setw(12) << ma_xe
         << setw(15) << loai_xe
         << setw(12) << gio_vao
         << setw(12) << tg_do
         << fixed << setprecision(0)
         << tinh_phi() << " VND\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
    bool day() const;
    int so_luong() const;
};

bai_xe::bai_xe() {
    ma_bai = 0;
    kich_thuoc = 'S';
    co1 = false;
    co2 = false;
    co3 = false;
}

bai_xe::bai_xe(int ma, char kt) {
    ma_bai = ma;
    kich_thuoc = kt;
    co1 = false;
    co2 = false;
    co3 = false;
}

int bai_xe::lay_ma() const {
    return ma_bai;
}

int bai_xe::so_luong() const {
    return (co1 ? 1 : 0) +
           (co2 ? 1 : 0) +
           (co3 ? 1 : 0);
}

bool bai_xe::day() const {
    int cap = (kich_thuoc == 'S') ? 1 :
              (kich_thuoc == 'M') ? 2 : 3;

    return so_luong() >= cap;
}

bool bai_xe::them(phuong_tien v) {
    int cap = (kich_thuoc == 'S') ? 1 :
              (kich_thuoc == 'M') ? 2 : 3;

    if (day())
        return false;

    if (cap >= 1 && !co1) {
        pt1 = v;
        co1 = true;
        return true;
    }

    if (cap >= 2 && !co2) {
        pt2 = v;
        co2 = true;
        return true;
    }

    if (cap >= 3 && !co3) {
        pt3 = v;
        co3 = true;
        return true;
    }

    return false;
}

bool bai_xe::xoa(int ma_xe) {
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
        if (co2) {
            pt1 = pt2;

            if (co3) {
                pt2 = pt3;
                co3 = false;
            }
            else {
                co2 = false;
            }
        }
        else {
            co1 = false;
        }

        return true;
    }

    if (co2 && pt2.lay_ma_xe() == ma_xe) {
        if (co3) {
            pt2 = pt3;
            co3 = false;
        }
        else {
            co2 = false;
        }

        return true;
    }

    if (co3 && pt3.lay_ma_xe() == ma_xe) {
        co3 = false;
        return true;
    }

    return false;
}

bool bai_xe::chua(int ma_xe) const {
    if (co1 && pt1.lay_ma_xe() == ma_xe)
        return true;

    if (co2 && pt2.lay_ma_xe() == ma_xe)
        return true;

    if (co3 && pt3.lay_ma_xe() == ma_xe)
        return true;

    return false;
}

void bai_xe::hien_thi() const {
    int cap = (kich_thuoc == 'S') ? 1 :
              (kich_thuoc == 'M') ? 2 : 3;

    cout << "\nBai " << ma_bai
         << " [" << kich_thuoc << "] "
         << so_luong() << "/" << cap << " xe\n";

    if (so_luong() == 0) {
        cout << "Bai xe trong!\n";
        return;
    }

    cout << left
         << setw(12) << "Ma xe"
         << setw(15) << "Loai xe"
         << setw(12) << "Gio vao"
         << setw(12) << "TG do"
         << "Phi do xe\n";

    if (co1) pt1.hien_thi();
    if (co2) pt2.hien_thi();
    if (co3) pt3.hien_thi();
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0;
    tong = 0;

    if (co1 && pt1.lay_loai_xe() == loai) {
        ++dem;
        tong += pt1.tinh_phi();
    }

    if (co2 && pt2.lay_loai_xe() == loai) {
        ++dem;
        tong += pt2.tinh_phi();
    }

    if (co3 && pt3.lay_loai_xe() == loai) {
        ++dem;
        tong += pt3.tinh_phi();
    }

    return dem > 0;
}

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

    bool trung_ma_bai(int ma) const {
        if (co1 && bai1.lay_ma() == ma)
            return true;

        if (co2 && bai2.lay_ma() == ma)
            return true;

        if (co3 && bai3.lay_ma() == ma)
            return true;

        return false;
    }

    bool trung_ma_xe(int ma) const {
        if (co1 && bai1.chua(ma))
            return true;

        if (co2 && bai2.chua(ma))
            return true;

        if (co3 && bai3.chua(ma))
            return true;

        return false;
    }

    bool chuan_hoa_loai(string& loai) const {
        for (int i = 0; i < (int)loai.length(); i++) {
            loai[i] = tolower(
                static_cast<unsigned char>(loai[i])
            );
        }

        if (loai == "car")
            loai = "Car";
        else if (loai == "motorcycle")
            loai = "Motorcycle";
        else if (loai == "bicycle")
            loai = "Bicycle";
        else
            return false;

        return true;
    }

    void bao_cao_bai(const bai_xe& bai) const {
        int dem;
        double tong;

        cout << "\nBai " << bai.lay_ma() << ":\n";

        if (bai.co_loai("Car", dem, tong))
            cout << "Car: " << tong / dem << " VND\n";
        else
            cout << "Car: Chua co xe\n";

        if (bai.co_loai("Motorcycle", dem, tong))
            cout << "Motorcycle: " << tong / dem << " VND\n";
        else
            cout << "Motorcycle: Chua co xe\n";

        if (bai.co_loai("Bicycle", dem, tong))
            cout << "Bicycle: " << tong / dem << " VND\n";
        else
            cout << "Bicycle: Chua co xe\n";
    }

    void liet_ke_loai(const bai_xe& bai,
                      string loai,
                      bool& tim_thay) const {
        int dem;
        double tong;

        if (bai.co_loai(loai, dem, tong)) {
            tim_thay = true;
            bai.hien_thi();
        }
    }

public:
    SystemInterface();

    void runMenu();
};

SystemInterface::SystemInterface() {
    co1 = false;
    co2 = false;
    co3 = false;
}

void SystemInterface::runMenu() {
    int chon;

    while (true) {
        cout << "\n========== QUAN LY BAI DO XE ==========\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";

        if (!(cin >> chon)) {
            cout << "Du lieu khong hop le!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (chon == 1) {
            int ma;
            char kt;

            cout << "Nhap ma bai: ";
            cin >> ma;

            if (trung_ma_bai(ma)) {
                cout << "Ma bai da ton tai!\n";
                continue;
            }

            cout << "Nhap kich thuoc (S/M/L): ";
            cin >> kt;

            kt = toupper(static_cast<unsigned char>(kt));

            if (kt != 'S' && kt != 'M' && kt != 'L') {
                cout << "Kich thuoc khong hop le!\n";
                continue;
            }

            if (!co1) {
                bai1 = bai_xe(ma, kt);
                co1 = true;
            }
            else if (!co2) {
                bai2 = bai_xe(ma, kt);
                co2 = true;
            }
            else if (!co3) {
                bai3 = bai_xe(ma, kt);
                co3 = true;
            }
            else {
                cout << "Da du 3 bai xe!\n";
                continue;
            }

            cout << "Tao bai xe thanh cong!\n";
        }

        else if (chon == 2) {
            int ma, gio, tg;
            string loai;

            cout << "Nhap ma xe: ";
            cin >> ma;

            if (trung_ma_xe(ma)) {
                cout << "Ma xe da ton tai!\n";
                continue;
            }

            cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
            cin >> loai;

            if (!chuan_hoa_loai(loai)) {
                cout << "Loai xe khong hop le!\n";
                continue;
            }

            cout << "Nhap gio vao (0-23): ";
            cin >> gio;

            if (gio < 0 || gio > 23) {
                cout << "Gio vao khong hop le!\n";
                continue;
            }

            cout << "Nhap thoi gian do (1-23): ";
            cin >> tg;

            if (tg < 1 || tg > 23) {
                cout << "Thoi gian do khong hop le!\n";
                continue;
            }

            phuong_tien v(ma, loai, gio, tg);

            bool thanh_cong = false;

            if (co1 && bai1.them(v))
                thanh_cong = true;
            else if (co2 && bai2.them(v))
                thanh_cong = true;
            else if (co3 && bai3.them(v))
                thanh_cong = true;

            if (thanh_cong)
                cout << "Them xe thanh cong!\n";
            else
                cout << "Khong con cho trong!\n";
        }

        else if (chon == 3) {
            int ma;

            cout << "Nhap ma bai can xoa: ";
            cin >> ma;

            if (co1 && bai1.lay_ma() == ma) {
                bai1 = bai_xe();
                co1 = false;
                cout << "Xoa bai thanh cong!\n";
            }
            else if (co2 && bai2.lay_ma() == ma) {
                bai2 = bai_xe();
                co2 = false;
                cout << "Xoa bai thanh cong!\n";
            }
            else if (co3 && bai3.lay_ma() == ma) {
                bai3 = bai_xe();
                co3 = false;
                cout << "Xoa bai thanh cong!\n";
            }
            else {
                cout << "Khong tim thay bai xe!\n";
            }
        }

        else if (chon == 4) {
            int ma;

            cout << "Nhap ma xe can lay ra: ";
            cin >> ma;

            bool ket_qua = false;

            if (co1 && bai1.xoa(ma))
                ket_qua = true;
            else if (co2 && bai2.xoa(ma))
                ket_qua = true;
            else if (co3 && bai3.xoa(ma))
                ket_qua = true;

            if (ket_qua)
                cout << "Lay xe ra thanh cong!\n";
            else
                cout << "Khong tim thay xe!\n";
        }

        else if (chon == 5) {
            if (!co1 && !co2 && !co3) {
                cout << "He thong chua co bai xe!\n";
                continue;
            }

            if (co1) bai1.hien_thi();
            if (co2) bai2.hien_thi();
            if (co3) bai3.hien_thi();
        }

        else if (chon == 6) {
            int ma;

            cout << "Nhap ma bai xe: ";
            cin >> ma;

            if (co1 && bai1.lay_ma() == ma)
                bai1.hien_thi();
            else if (co2 && bai2.lay_ma() == ma)
                bai2.hien_thi();
            else if (co3 && bai3.lay_ma() == ma)
                bai3.hien_thi();
            else
                cout << "Khong tim thay bai xe!\n";
        }

        else if (chon == 7) {
            string loai;

            cout << "Nhap loai xe: ";
            cin >> loai;

            if (!chuan_hoa_loai(loai)) {
                cout << "Loai xe khong hop le!\n";
                continue;
            }

            bool tim_thay = false;

            if (co1)
                liet_ke_loai(bai1, loai, tim_thay);

            if (co2)
                liet_ke_loai(bai2, loai, tim_thay);

            if (co3)
                liet_ke_loai(bai3, loai, tim_thay);

            if (!tim_thay)
                cout << "Khong tim thay xe!\n";
        }

        else if (chon == 8) {
            int dem = 0;
            double tong = 0;

            if (!co1 && !co2 && !co3) {
                cout << "He thong chua co bai xe!\n";
                continue;
            }

            cout << "\n===== BAO CAO THEO TUNG BAI =====\n";

            if (co1) bao_cao_bai(bai1);
            if (co2) bao_cao_bai(bai2);
            if (co3) bao_cao_bai(bai3);

            cout << "\n===== TRUNG BINH TOAN HE THONG =====\n";

            if (co1) {
                bai1.co_loai("Car", dem, tong);
                if (dem > 0) {
                    static double carTotal = 0;
                    carTotal += tong;
                }
            }

            double carTotal = 0;
            double motoTotal = 0;
            double bicycleTotal = 0;

            int carCount = 0;
            int motoCount = 0;
            int bicycleCount = 0;

            if (co1) {
                bai1.co_loai("Car", dem, tong);
                carTotal += tong;
                carCount += dem;

                bai1.co_loai("Motorcycle", dem, tong);
                motoTotal += tong;
                motoCount += dem;

                bai1.co_loai("Bicycle", dem, tong);
                bicycleTotal += tong;
                bicycleCount += dem;
            }

            if (co2) {
                bai2.co_loai("Car", dem, tong);
                carTotal += tong;
                carCount += dem;

                bai2.co_loai("Motorcycle", dem, tong);
                motoTotal += tong;
                motoCount += dem;

                bai2.co_loai("Bicycle", dem, tong);
                bicycleTotal += tong;
                bicycleCount += dem;
            }

            if (co3) {
                bai3.co_loai("Car", dem, tong);
                carTotal += tong;
                carCount += dem;

                bai3.co_loai("Motorcycle", dem, tong);
                motoTotal += tong;
                motoCount += dem;

                bai3.co_loai("Bicycle", dem, tong);
                bicycleTotal += tong;
                bicycleCount += dem;
            }

            cout << fixed << setprecision(0);

            cout << "Car: "
                 << (carCount > 0 ? carTotal / carCount : 0)
                 << " VND\n";

            cout << "Motorcycle: "
                 << (motoCount > 0 ? motoTotal / motoCount : 0)
                 << " VND\n";

            cout << "Bicycle: "
                 << (bicycleCount > 0 ? bicycleTotal / bicycleCount : 0)
                 << " VND\n";
        }

        else if (chon == 9) {
            cout << "Ket thuc chuong trinh!\n";
            break;
        }

        else {
            cout << "Lua chon khong hop le!\n";
        }
    }
}

int main() {
    SystemInterface ql;
    ql.runMenu();

    return 0;
}
```

Luu ý: Code s? d?ng dúng tên phuong th?c b?n yêu c?u. Không có m?ng, vector hay con tr?. Phí d? xe áp d?ng h? s? cao di?m/th?p di?m theo gi? vào bãi cho hai gi? d?u tiên.
