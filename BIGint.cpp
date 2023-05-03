    #include <iostream>
    #include <string>
    #include <vector>
    #include <algorithm>
    

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
        
        int length(){
            return x.size();
        }
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
        // "stripping" the "-" sign if possible
        void strip(){
            if (x.at(0)=='-'){
                x.erase(x.begin()+0);
                str = true;
            }
        }
        // restoring the "-" sign after the desired operation
        void unstrip(){
            if (str){
                x.insert(0,"-");
                str = false;
            }
        }
        // Check if some number is bigger than this
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
                for (int z=0;z<i;z++){
                    int prvi, drugi;
                    prvi = this->x.at(z) - '0';
                    drugi = a.x.at(z) - '0';
                    if (prvi<drugi)
                        return true;
                    else if (prvi>drugi) return false;
                }
            }
            if (neg()&&!neg(a)) 
                return true;
            if (!neg()&&neg(a))
                return false;
            if (neg()&&neg(a)){
                if (i<j) return false;
                else if (i>j) return true;
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
        
        void Zero(){
            if (x.size()>1)
                if (x.at(0)=='0'){
                    //std::cout << "Znaci radim nesto tebro\n";
                    x.erase(x.begin()+0);
                }
        }
        
        void operator=(std::string a){
            // input check
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
            
            // + & - || EXOR 
            if (neg()!=neg(a)){
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
                    
                return y; 
            }
            
            // - & - 

            if (neg()&&neg(a)){
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
            
            // + & +
            int i = a.x.size()-1;
            int j = this->x.size()-1;
            
            while (true){
                if (i<0 && j<0)
                    break;
                    
                if (i>=0)
                    prvi = a.x.at(i) - '0';
                else prvi = 0;
                if (j>=0)
                    drugi = this->x.at(j) - '0';
                else drugi = 0;
                
                zbir += prvi + drugi;

                if (zbir>9){
                    y.x+=std::to_string(zbir%10);
                    zbir=1;
                }
                else{
                    y.x+=std::to_string(zbir);
                    zbir = 0;
                }

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
            
            if (x==a.x)
            {
                y.x="0";
                return y;
            }
            
            // - & - 
            if (neg()&&neg(a)){
                STRIP = true;
                a.strip();
                strip();
            }
            // + & - 
            if (!neg()&&neg(a)){
                a.strip();
                a.unstrip();
                return *this+a;
            }
            // - & +
            if (neg()&&!neg(a)){
                strip();
                y = *this+a;
                y.x.insert(0,"-");
                return y;
            }
            
            int i = a.x.size()-1;
            int j = this->x.size()-1;
            // checking which number is bigger (essential for substracting operation)
            flag = veci(a); 
            
            // + & +
            
            while (true){
                if (i<0 && j<0)
                    break;
                if (flag){
                    if (i>=0) prvi = a.x.at(i) - '0'; // ASCII conversion
                    else prvi = 0;
                    if (j>=0) drugi = this->x.at(j) - '0';
                    else drugi = 0;
                }
                else{
                    if (j>=0) prvi = this->x.at(j) - '0';
                    else prvi = 0;
                    if (i>=0) drugi = a.x.at(i) - '0';
                    else drugi = 0;
                }
                prvi -= prenos;
                prenos = 0;
                
                if (prvi<drugi){
                    prvi+=10;
                    prenos = 1;
                }
                
                raz = prvi - drugi;
                
                y.x+=std::to_string(raz);
                
                i--;
                j--;
            }
            
            // mopping up stray zeroes
            if (y.x.at(y.x.size()-1)=='0')
                y.x.erase(y.x.begin()+y.x.size()-1);
            
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
            std::vector<std::string> k; // storing multiplication "fragments here"
            
            // + & -
            if (neg()&&neg(a.x)){
                strip();
                a.strip();
            }
            
            if (neg()!=neg(a.x)){
                strip();
                a.strip();
                flag = true;
            }
            // - & -
            
            if (x=="0"||a.x=="0")
                return y.x = "0";
            if (x=="0"&&a.x=="0")
                return y.x = "0";
            
            for (int i=a.x.size()-1;i>=0;i--){
                k.emplace_back();
                prvi = a.x.at(i) - '0';
                pro = 0;
                for (int j=this->x.size()-1;j>=0;j--){
                        drugi = this->x.at(j) - '0';
                        pro += prvi * drugi;
                        if (pro>9){
                            k.back()+=std::to_string(pro%10);
                            pro/=10;
                        }
                        else{
                            k.back()+=std::to_string(pro);
                            pro = 0;
                        }
                    }
                if(pro) k.back()+=std::to_string(pro);
            }
            std::string br;
            std::vector<BIG> temp;
            for (auto&x : k){
                std::reverse(x.begin(),x.end());
                x+=br;
                br+= "0";

                temp.emplace_back();
                temp.back().x = x;

            }

            // adding up the "fragments"
            for (auto& x: temp){
                if (y.x.empty())
                    y = x;
                else  y = y + x;
            }
                
            if (flag&&y.x!="0")
                y.x.insert(0,"-");
            
            unstrip();
            a.unstrip();
            
            return y;
            
        }
        
        BIG operator/(BIG a){

            BIG y,s,tmp,pom;
            
            BIG pro;
            
            int i = 0;
            bool dali = false, pljus = false;
            
            
            if (this->x==a.x){
                if(neg()!=neg(a.x))
                y.x = "-1";
                else y.x = "1";
                return y;
            }
            
            if (a.x == "0"){
                std::cout << "Smooth move, but i'm afraid we cannot divide by zero...\n";
                return y;
            }
            
            // + & -
            
            if (neg()&&neg(a.x)){
                strip();
                a.strip();
                pljus = false;
            }
            
            else if (neg()!=neg(a.x)){
                strip();
                a.strip();
                pljus = true;
            }

            // - & -
            // + & + 
            
            while (true){
                if (i>this->x.size()-1)
                    break;
                
                s.x+=this->x.at(i);
                
                tmp.x.clear();

                for (int j=1;j<=9;j++){
                    pom.x=std::to_string(j);
                    pro = a*pom;
                    BIG prox = s-pro;
                    if(neg(prox)){
                        break;
                    }
                    else {
                        tmp=std::to_string(j);
                        dali = true;
                    }
                }
                if (dali) {
                    s = s-a*tmp;
                    dali = false;
                }
            
                y.x+=tmp.x;
                    
                i++;

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
        
        // modulo
        BIG operator%(BIG a){
            BIG y,s,tmp,pom;
            
            BIG pro;
            
            int i = 0;
            bool dali = false;
    
            
            if (a.x == "0"){
                std::cout << "Smooth move, but i'm afraid we cannot divide by zero...\n";
                return y;
            }
            
            if (neg()!=neg(a.x)){
                strip();
                a.strip();
            }
            
            while (true){
                if (i>this->x.size()-1)
                    break;
                
                s.x+=this->x.at(i);
                
                
                tmp.x.clear();

                for (int j=1;j<=9;j++){
                    pom.x=std::to_string(j);
                    pro = a*pom;
                    if(neg(s-pro)){
                        break;
                    }
                    else {
                        tmp=std::to_string(j);
                        dali = true;
                    }
                }
                if (dali) {
                    s = s-a*tmp;
                    dali = false;
                }
                
                i++;
                    
            }
            
            y=s;
            
            unstrip();
            a.unstrip();
            
            if (y.x.size()>1)
                if (y.x.at(0)=='0')
                    y.x.erase(y.x.begin()+0);

            return y;
            
        }
        // raise to the power
        BIG operator^(int a){
            BIG y = *this;
                
            for(int i=0;i<a-1;i++)
                y = y*(*this);
            
            return y;
        }
        // Convert an integer to a big integer.
        void operator=(int a){
            this->x.clear();
            
            int b = a;
            int i = 10;
            if (a<0){
                b = a * -1;
            }
            while (b/i){
                this->x+=std::to_string(b%i);
                b = b/i;
            }
            this->x+=std::to_string(b%i);
            if (a<0)
                this->x+="-";
            std::reverse(this->x.begin(),this->x.end());
        }
        // square root || Cringerana
        BIG sqrt(){
            int i = 0;
            bool odd = false, first = true;
            BIG s,d,c;
            BIG pom,wtf;
            BIG y;
            
            if (neg())
                strip();
            
            if (length()%2)
                odd = true;
            
            while (i<length()){
                if (odd){
                    s.x+=x.at(i);
                    i++;
                }
                else {
                    s.x+=x.at(i);
                    i++;
                    s.x+=x.at(i);
                    i++; 
                }
                
                
                if (first){
                    for (int i=1;i<10;i++){
                            d = i;
                            d = d^2;
                            if (neg(s-d)){
                                pom = s-d;
                                d = (i-1);
                                y = d;
                                c = d*d;
                                s = s - c; // ono sto se deli
                                first = false;
                                break;
                            }
                            else if (i==9) {
                                d = i;
                                y = d;
                                c = d*d;
                                s = s - c;
                                first = false;
                            }
                    }
                    d = d + d;
                }
                else{

                    s.Zero();
                    
                    for (int i=0;i<10;i++){
                        c = i;
                        pom.x = d.x + c.x;
                        pom = pom*c;
                        pom = s - pom;
                        if (pom.x=="0"){
                            y.x+=std::to_string(i);
                            wtf = "0";
                            break;
                        }
                        if (neg(pom)){
                            //if (!i)
                                //y.x+="0";
                            y.x+=std::to_string(i-1);
                            c = i-1;
                            break;
                        }
                        if (i==9){
                            y.x+=std::to_string(i);
                            c = i;
                        }
                        wtf = pom;
                    }
                    
                    s = wtf;
                    pom.x = d.x + c.x;
                    d = pom + c;

                }
                
                odd = false;
            }
            
            std::cout << "Eve ga: " << y.x << "\n";
            
            unstrip();
            return y;
        }
        
    };
    
    int main() {
        BIG x {"225"};
        BIG y {"129"};
        BIG c {"-2"};
        
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
        
        z = x % y;
        z.print();
        std::cout << "%\n";
        
        z = c^3;
        z.print();
        std::cout << "^\n";
        
        
        z = "4878044649";
        z.sqrt();
        std::cout << "\n";
        
        /*
        for (int i=1000;i<1200;i++){
            int a = i*i;
            std::cout << "a: " << a << " sqrt";
            z = a;
            z.sqrt();
            std::cout << "\n";
        }*/
        
        
        return 0;
    }
