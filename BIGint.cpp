    #include <iostream>
    #include <string>
    #include <vector>
    #include <algorithm>
    
    // BRDO std::cout-ova sam koristio za brzo nalazenje gresaka, plus me mrzi da palim VSCODE i debugger
    // sve sto ne zahteva rad sa fajlovima radim preko online compilera kek. Alfa chad bobi <3 <3 <3

    class BIG{
        std::string x;
        bool str = false;
        public:
        BIG(){}
        BIG(std::string new_x) {
            x = new_x;
        }
        void print(){
            std::cout << x << " ";
        }
        // overloading operators + za pocetak
        // razlicita duzina brojeva <3 <3 <3
        // problematika negativno pozitivnih sranja
        // Suvisno imati dve funkcije za proveru NEG stanja ali me mrzelo da kucam
        // neg(x)&&neg(a.x); Yes, napisao sam funkciju da bi kucao jedno slovo manje -> neg() kek;
        bool neg(BIG a){
            if (a.x.at(0)=='-')
                return true;
            else return false;
        }
        bool neg(){
            if (x.at(0)=='-')
                return true;
            else return false;
        }
        // "stripovanje" znaka negativnosti pred operaciju
        void strip(){
            if (x.at(0)=='-'){
                x.erase(x.begin()+0);
                str = true;
            }
        }
        void unstrip(){
            if (str){
                x.insert(0,"-");
                str = false;
            }
        }
        // Za operacije oduzimanja, deljenja je vrlo bitno koj je od dva broja veci stoga funkcija/metod
        bool veci(BIG a){
            int i,j;
            i = this->x.size();
            j = a.x.size();
            
            if (this->x==a.x)
                return true;
            if (!neg()&&!neg(a)){
                if (i<j)
                    return true;
                else if (i>j) return false;
                // ako su jednaki
                for (int z=0;z<i;z++){
                    //std::cout << x.at(z) << " " << a.x.at(z) << "\n";
                    int prvi, drugi;
                    prvi = this->x.at(z) - '0';
                    drugi = a.x.at(z) - '0';
                    if (prvi<drugi)
                        return true;
                    else if (prvi>drugi) return false;
                }
            }
            // ako je samo jedan negativan ez slucaj
            if (neg()&&!neg(a)) // exor
                return true;
            if (!neg()&&neg(a))
                return false;
            // ako su oba negativna onda mora razmislimo
            if (neg()&&neg(a)){
                if (i<j) return false;
                else if (i>j) return true;
                // ako su jednaki
                for (int z=1;z<i;z++){
                    int prvi, drugi;
                    prvi = this->x.at(z) - '0';
                    drugi = a.x.at(z) - '0';
                   if (prvi<drugi)
                        return true;
                    else if (prvi>drugi) return false;
                }
            }
            
        }
        
        void operator=(std::string a){
            // sprecavamo dodelu bilo cega sto nije - ili brojka
            for (auto& x: a)
                if (((int)x<48 || (int)x>57)&&((int)x!=45)){
                    std::cout << "Invalid input, pls ne zebavaj sa slovca\n";
                    std::cout << (int)x << "\n";
                    return;
                    }
            x = a;
        }
        
        BIG operator+(BIG a){
            BIG y;
            int prvi, drugi;
            int zbir = 0;
            
            bool STRIP = false;
            
            // + i - || EXOR || CRINGE
            if (neg()!=neg(a)){
                //std::cout << "Preduslov1\n";
                if (veci(a))
                    STRIP = true;
                a.strip();
                strip();
                y = *this-a;
                
                if (STRIP){
                    if (y.x.at(0)=='-')
                        y.x.erase(y.x.begin()+0);
                    else y.x.insert(0,"-");
                }
                    
                return y; // dobar prototip
            }
            
            
            // - i - 
            // if minus minus STRIP operacija i dodamo minus na kraju
            if (neg()&&neg(a)){
                //std::cout << "Preduslov2\n";
                a.strip();
                strip();
                STRIP = true;
            }
            
            // ZERO Case
            if (x=="0"&&a.x!="0")
                return a;
            if (x!="0"&&a.x=="0")
                return *this;
            if (x=="0"&&a.x=="0")
                return *this;
            // ZERO CASE
            
            // + i +
            int i = a.x.size()-1;
            int j = this->x.size()-1;
            
            
            while (true){
                if (i<0 && j<0)
                    break;
                    
                if (i>=0)
                    prvi = a.x.at(i) - '0';
                else prvi = 0;
                if (j>=0)
                    drugi = this->x.at(j) - '0'; // out of range 100%.
                else drugi = 0;
                
                //std::cout << "prvi: " << prvi << " drugi " << drugi << "\n";
                zbir += prvi + drugi;
                //std::cout << "zbir: " << zbir << "\n";
                if (zbir>9){
                    y.x+=std::to_string(zbir%10);
                    //std::cout << zbir%10 << "\n";
                    zbir=1;
                }
                else{
                    y.x+=std::to_string(zbir);
                    zbir = 0;
                }
                //std::cout << prvi+drugi << " ";
                i--;
                j--;
            }
            if (zbir)
                y.x+=std::to_string(zbir);
            std::reverse(y.x.begin(),y.x.end());
            
            if (STRIP)
                y.x.insert(0,"-");
            
            
            unstrip();
            a.unstrip();
            
            return y;
        }
        
        BIG operator-(BIG a){
            BIG y;
            int prvi, drugi;
            int raz, prenos = 0;
            bool flag = false,STRIP = false;
            
            // + i + || normalno
            // - i - || relegiramo na + operaciju i dodamo minus na kraju
            
            // + i - slucaj
            // - i + slucaj
            
            if (x==a.x)
            {
                y.x="0";
                return y;
            }
            
            //std::cout << "Prvi: " << x << " Drugi: " << a.x << "\n";
            // - i - || PROBLEMATICNO
            if (neg()&&neg(a)){
                //std::cout << "Ovde treba bit\n";
                STRIP = true;
                a.strip();
                strip();
                //std::cout << "Prvi: " << x << " Drugi: " << a.x << "\n";
            }
            // + i - 
            if (!neg()&&neg(a)){
                a.strip();
                //std::cout << a.x << "\n";
                return *this+a;
            }
            // - i +
            if (neg()&&!neg(a)){
                strip();
                y = *this+a;
                y.x.insert(0,"-");
                return y;
            }
            
            int i = a.x.size()-1;
            int j = this->x.size()-1;
            flag = veci(a); // Za oduzimanje je apsolutni imperativ da veci bude prvi broj.
            
            //std::cout << "Flag je: " << flag << "\n";
            
            // + i + slucaj regularan
            //std::cout << "Prvi: " << x << " Drugi: " << a.x << "\n";
            while (true){
                if (i<0 && j<0)
                    break;
                if (flag){
                    if (i>=0) prvi = a.x.at(i) - '0'; // Ascii forica za konverziju char-ova u int;
                    else prvi = 0;
                    if (j>=0) drugi = this->x.at(j) - '0';
                    else drugi = 0;
                }
                else{
                    if (j>=0) prvi = this->x.at(j) - '0';
                    else prvi = 0;
                    if (i>=0) drugi = a.x.at(i) - '0';
                    else drugi = 0;
                    //std::cout << "Upad\n";
                }
                //std::cout << "Prvi: " << prvi << " Drugi: " << drugi << "\n";
                prvi -= prenos;
                prenos = 0;
                if (prvi<drugi){
                    prvi+=10;
                    prenos = 1;
                }
                //std::cout << "Prvi: " << prvi << " Drugi: " << drugi << "\n";
                raz = prvi - drugi;
                
                y.x+=std::to_string(raz);
                //std::cout << "Tekuci string " << y.x << "\n";
                
                i--;
                j--;
            }
            
            // ciscenje nula prilikom oduzimanja, nevermind mrzi me da objasnjavam
            if (y.x.at(y.x.size()-1)=='0')
                y.x.erase(y.x.begin()+y.x.size()-1);
            
            //std::cout << "Flag je: " << flag << "\n";

            std::reverse(y.x.begin(),y.x.end());
            
            if (flag)
                y.x.insert(0,"-");
            if (STRIP){
                if(y.x.at(0)=='-')
                y.x.erase(y.x.begin()+0);
                else y.x.insert(0,"-");
            }

            unstrip();
            a.unstrip();
            
            return y;
        }
        
        BIG operator*(BIG a){
            BIG y;
            int prvi, drugi;
            int pro = 0;
            bool flag = false;
            std::vector<std::string> k;
            
            // + i + || nista
            // + i -
            if (neg()&&neg(a.x)){
                strip();
                a.strip();
            }
            
            if (neg()!=neg(a.x)){
                strip();
                a.strip();
                flag = true;
            }
            // - i -
            
            if (x=="0"||a.x=="0")
                return y.x = "0";
            if (x=="0"&&a.x=="0")
                return y.x = "0";
            
            for (int i=a.x.size()-1;i>=0;i--){
               // std::cout << "Upad\n";
                k.emplace_back();
                prvi = a.x.at(i) - '0';
                pro = 0;
                for (int j=this->x.size()-1;j>=0;j--){
                        drugi = this->x.at(j) - '0';
                        //std::cout << prvi << " " << drugi << "\n";
                        pro += prvi * drugi;
                        if (pro>9){
                            //std::cout << "Pro je: " << pro << "\n";
                            k.back()+=std::to_string(pro%10);
                            //std::cout << "Pro je: " << pro%10 << "\n";
                            pro/=10;
                        }
                        else{
                            //std::cout << "Pro je: " << pro << "\n";
                            k.back()+=std::to_string(pro);
                            pro = 0;
                        }
                    }
                if(pro) k.back()+=std::to_string(pro);
                //std::cout << "Tekuci mnozitelj " << a.x.at(i) << "\n";
                //std::cout << "Tekuci string: " << k.back() << "\n";
            }
            //std::cout << "Ispad\n";
            std::string br;
            std::vector<BIG> temp;
            for (auto&x : k){
                std::reverse(x.begin(),x.end());
                x+=br;
                br+= "0";
                //std::cout << x << "\n";
                temp.emplace_back();
                temp.back().x = x;
                //std::cout << x << "\n";
            }
            //std::cout << "Ispad\n";
            //std::cout << temp.size() << "\n";

            for (auto& x: temp){
                if (y.x.empty())
                    y = x;
                else 
                //std::cout << x.x << "\n";
                y = y + x;
            }
                
            // std::cout << "Ispad\n";
            if (flag&&y.x!="0")
                y.x.insert(0,"-");
            
                
            unstrip();
            a.unstrip();
            
                
            return y;
            
        }
        
        BIG operator/(BIG a){ 

            // SLUCAJ 1: moze da se podeli
            // SLUCAJ 2: deljenje sa ostatkom; odbacis ostatak
            // SLUCAJ 3: ne moze da se podeli -> 0
            // kao ocisceno od bagova ali pitaj kurac da li ce i kako da radi kekerinos

            BIG y,s,tmp,pom;
            
            BIG pro,lab; // govna
            
            int i = 0;
            bool dali = false, pljus = false;
            
            
            if (this->x==a.x){
                //std::cout << "Jedan\n";
                if(neg()!=neg(a.x))
                y.x = "-1";
                else y.x = "1";
                return y;
            }
            
            if (a.x == "0"){
                std::cout << "Ne mozemo deliti nulom ciganine mali...\n";
                return y;
            }
            
            // + i -
            // bool prase !- bool dabar -> ekvivalent EXOR-u
            //std::cout << x << " " << a.x << "\n";
            
            if (neg()&&neg(a.x)){
                //std::cout << "Dva\n";
                strip();
                a.strip();
                pljus = false;
            }
            
            else if (neg()!=neg(a.x)){
                //std::cout << "Tri\n";
                strip();
                a.strip();
                pljus = true;
            }
            
            BIG b = a.x;

            // - i -
            // + i + 
            
            while (true){
                if (i>this->x.size()-1)
                    break;
                
                s.x+=this->x.at(i);
                
                
                tmp.x.clear();

                for (int j=1;j<=9;j++){
                    pom.x=std::to_string(j);
                    pro = b*pom;
                    pro.strip();
                    lab = s-pro;
                    if(neg(s-pro)){
                        //std::cout << "Za " << s.x << " nemam go kurac\n";
                        BIG prop;
                        prop = s-pro;
                        break;
                    } // problematicno jer nije moja klasa =-=; 
                    else {
                        tmp=std::to_string(j);
                        dali = true;
                    }
                }
                if (dali) {
                    s = s-b*tmp;
                    dali = false;
                }
            
                y.x+=tmp.x;
                    
                i++;
                // nema vise stringova a nismo nasli sadrzalac
                if (i>this->x.size()-1)
                    if (tmp.x.empty())
                        y.x+="0";
                    
            }
            
            if (pljus&&y.x!="0")
                y.x.insert(0,"-");
            
            unstrip();
            a.unstrip();

            return y;
        }
        
    };
    
    int main() {
        /*
        BIG x {"123"};
        BIG y {"227"};
        
        BIG x {"2460"};
        BIG y {"861"};
        BIG x {"134"};
        BIG y {"7"};
        */
    
        BIG x {"-56"};
        BIG y {"90"};
        
        
        BIG z;
        

        z = x + y;
        z.print();
        std::cout << "+\n";
        z = x - y;
        z.print();
        std::cout << "-\n";
        z = x * y;
        z.print();
        std::cout << "*\n";
        z = x / y;
        z.print();
        std::cout << "/\n";
        
    
        return 0;
    }
