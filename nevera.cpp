#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct comida_tienda{
    string alimento, categoria; //categor
    int stock, fcaducidad;
    double precio;
};

struct comida_nevera{
    string alimento;
    int stock, fcompra, fcaduc;
};

struct comida_pref{
    string comida;
    int MinStock;
};

struct nevera{
    string usuario, contrasena,direccion;
    int credito;
    vector<comida_nevera> enlanevera;
    vector<comida_pref> preferente;
};
vector<nevera> listaneveras;

struct tienda{
    string direccion, horario;
    vector<comida_tienda> stocktienda;
};

struct cesta{
    int cantidad;
    string nombre;
};
vector<cesta> listacesta;
vector<cesta> historial;

void escribircategorias (tienda X, int& N, int tindice);
void modificarcuenta (nevera& X, int& N);
void comidanevera (nevera X);
void menubuscarcomida (tienda X, int& N,vector<cesta> listacesta, cesta C );
void confirmarpedido(vector<cesta> listacesta, vector<cesta> historial, tienda& X, nevera A, int indice);
void buscartiendanombre_cesta (tienda X, vector<cesta> listacesta, cesta C);
void menucategorias(int &N, tienda X,vector<cesta> listacesta,cesta C, bool pref);
void menudietas(int &N, tienda X, vector<cesta> listacesta, cesta C);
void tiendacategoria_cesta(tienda X, vector<cesta> listacesta, cesta C,int N);

void menuprincipal (int& N){
    cout<<"-------------------------------------------------------" <<endl;
    cout<<"1. Usuario" <<endl
        <<"2. Ver comida que hay en la nevera" <<endl
        <<"3. Ver tienda" <<endl
        <<"4. Salir" <<endl;
    cin>>N;
}

void menuusuario (int& N, nevera X){
    cout<<"--------------------------------------------------------" <<endl;
    cout<<"1. Consultar cuenta" <<endl
        <<"2. Modificar cuenta" <<endl
        <<"3. Borrar cuenta" <<endl
        <<"4. Volver al menu principal" <<endl;
        cin>>N;
        switch(N){
        case 1:
            cout<<X.usuario<<" "<<X.contrasena<<" "<<X.credito<<" "<<X.direccion<<endl;
            break;
        case 2:
         //   if()
            modificarcuenta (X, N);
            break;
        case 3:
            X.usuario="0";
            X.contrasena="0";
            X.credito=0;
            X.direccion="0";
            X.enlanevera.clear();
            X.preferente.clear();
            break;
        case 4:
            menuprincipal (N);
            break;
    }
}

void modificarcuenta (nevera& X, int& N){
    string nombre,contrasena,direccion;
    int credito;

    cout<<"-----------------------------------------------------" <<endl;
    cout<<"1. modificar usuario" <<endl
        <<"2. modificar contrasena" <<endl
        <<"3. modificar targeta de credito" <<endl
        <<"4. Direccion" <<endl
        <<"5. Menu principal" <<endl;
    cin>>N;
    switch(N){
        case 1:  // falta guardar en la tupla y que vuelva algun sitio.
            cout<<"Introduce el nuevo nombre de usuario"<<endl;
            cin>>nombre;
            break;
        case 2:
            cout<<"Introduce la nuevo contraseña del usuario"<<endl;
            cin>>contrasena;
            break;
        case 3:
            cout<<"Introduce la nueva tarjeta de credito"<<endl;
            cin>>credito;
            break;
        case 4:
            cout<<"Introduce la nueva direccion del usuario"<<endl;
            cin>>direccion;
            break;
        case 5:
            break;
    }
}

void menucomidanevera (int& N, nevera X){
    cout<<"--------------------------------------------------------" <<endl;
    cout<<"1. Comida actual de la nevera" <<endl
        <<"2. Comida preferente actual" <<endl
        <<"3. Comida preferente que falta" <<endl
        <<"4. Volver al menu principal" <<endl;

    cin>>N;
    switch(N){
        case 1:
            comidanevera (X);
            break;
        case 2:
            break;
        case 3:
            break;
    }
}

void crearpreferencia (nevera& A, comida_pref& B){
    string nom;
    int stock;
    cout<<"¿Que comida quieres marcar como preferente? " <<endl;
    cin>>nom;
    B.comida=nom;
    cout<<"¿Cantidad?" <<endl;
    cin>>stock;
    B.comida=stock;
    A.preferente.push_back(B);
}

void menupreferente (nevera A, comida_pref B, int& N, bool& pref){
    cout<<"-------------------------------------------------------" <<endl;
    cout<<"1. Introducir por nombre" <<endl
        <<"2. Mirar en la tienda" <<endl
        <<"3. Volver" <<endl;
    cin>>N;
    switch(N){
        case 1:
            crearpreferencia (A, B);
            break;
        case 2:
            pref = true;
            break;
        case 3:
            break;

    }
}

void prefentetienda (){ //todavia no está empezada.

}

void comidanevera (nevera X){
    cout<<"-------------------------------------------------------" <<endl;
    for(int i=0; i<X.enlanevera.size(); i++){
        cout<<"Alimento: " <<X.enlanevera[i].alimento
            <<" Cantidad: " <<X.enlanevera[i].stock
            <<" Fecha de compra: " <<X.enlanevera[i].fcompra //hay que mirar como mostramos la fecha. Si queremos que se muestre 21/12/12 hay que hacer cambios.
            <<" Fecha de caducidad " <<X.enlanevera[i].fcaduc <<endl;
    }
}

void menupedido (int& N, tienda X, int tindice,vector<cesta> listacesta,
                 cesta C, bool& pref, vector<cesta> historial, nevera A, int indice){
    cout<<"------------------------------------------------------" <<endl;
    cout<<"Horario de disponibilidad de la tienda: " <<X.horario <<endl
    <<"Direccion: " <<X.direccion <<endl;
    cout<<"------------------------------------------------------" <<endl;
    cout<<"1. Buscar comida" <<endl
        <<"2. Cesta" <<endl
        <<"3. Historial pedidos" <<endl
        <<"4. Confirmar compra" <<endl
        <<"5. Menu principal" <<endl;
    switch (N){
        case 1:
          menubuscarcomida (X,N,listacesta,C);
          pref = false;
            break;
        case 2:
             for(int i=0; i<listacesta.size(); i++){
                cout<<listacesta[i].nombre <<" "
                    <<listacesta[i].cantidad  <<endl;
             }
            break;
        case 3:
            for(int i=0;i<historial.size();i++){
                cout<<historial[i].nombre<<" "<<historial[i].cantidad;
            }
            break;
        case 4:
              confirmarpedido(listacesta, historial, X, A, indice);
              //X es tienda; A es nevera.
            break;
        case 5:
             menuprincipal (N);
            break;
    }
}

void menubuscarcomida (tienda X, int& N, vector<cesta> listacesta, cesta C, bool pref ){
    cout<<"1. Buscar por nombre" <<endl
        <<"2. Buscar por categoria" <<endl
        <<"3. Buscar por dieta" <<endl
        <<"4. Volver" <<endl;
    cin>>N;
    switch (N){
        case 1:
            buscartiendanombre_cesta (X, listacesta, C);
            break;
        case 2:
             menucategorias(N, X, listacesta, C, pref);
            break;
        case 3:
            menudietas(N, X, listacesta, C);
            break;
        case 4:
            break;
    }

}

void buscartiendanombre_cesta (tienda X, vector<cesta> listacesta, cesta C, int& N, bool pref){
    string nombre;
    char comprar; //si o no añadir a la cesta.
    cout<<"¿Qué quieres buscar? " <<endl;
    cin>>nombre;
    for(int i=0; i<X.stocktienda.size(); i++){
        if(nombre==X.stocktienda[i].alimento){
            cout<<X.stocktienda[i].alimento <<" "
            <<X.stocktienda[i].precio <<" "
            <<X.stocktienda[i].fcaducidad <<endl;
            C.nombre = X.stocktienda[i].alimento;
        }
    }
    cout<<"Quires anadir el producto a la cesta? (s/n)" <<endl;
    cin>>comprar;
    if(comprar=='s'){
        cout<<"Cuantos? " <<endl;
        cin>>C.cantidad;
        listacesta.push_back(C);
    }else{
        menubuscarcomida (X, N, listacesta, C, pref);
    }
}

void menucategorias(int &N, tienda X,vector<cesta> listacesta,cesta C, bool pref){
    int cont=0;
    cout<<"------------------------------------------------------" <<endl;
    cout<<"1.Pescado" <<endl
        <<"2. Carne" <<endl
        <<"3. Lacteos" <<endl
        <<"4. Fruta" <<endl
        <<"5. Verdura" <<endl
        <<"6. Cereales"<<endl
        <<"7. Volver" <<endl;
    switch (N){
        case 1:
           for(int i=0;i<X.stocktienda.size();i++){
                if("Pescado"==X.stocktienda[i].categoria){
                    cout<<++cont<<"."<< X.stocktienda[i].alimento<<" Stock disponible: "
                    <<X.stocktienda[i].stock<<" Precio "<<X.stocktienda[i].precio<<endl;
                    tiendacategoria_cesta(X,listacesta,C,N);
            }
           }
            break;
        case 2:
             for(int i=0;i<X.stocktienda.size();i++){
                if("Carne"==X.stocktienda[i].categoria){
                    cout<<++cont<<"."<< X.stocktienda[i].alimento<<" Stock disponible: "
                        <<X.stocktienda[i].stock<<" Precio "<<X.stocktienda[i].precio<<endl;
                    tiendacategoria_cesta(X,listacesta,C,N);
            }
           }
            break;
        case 3:
             for(int i=0;i<X.stocktienda.size();i++){
                if("Lacteo"==X.stocktienda[i].categoria){
                    cout<<++cont<<"."<< X.stocktienda[i].alimento<<" Stock disponible: "
                        <<X.stocktienda[i].stock<<" Precio "<<X.stocktienda[i].precio<<endl;
                    tiendacategoria_cesta(X,listacesta,C,N);
            }
           }
            break;
        case 4:
             for(int i=0;i<X.stocktienda.size();i++){
                if("Fruta"==X.stocktienda[i].categoria){
                    cout<<++cont<<"."<< X.stocktienda[i].alimento<<" Stock disponible: "
                        <<X.stocktienda[i].stock<<" Precio "<<X.stocktienda[i].precio<<endl;
                    tiendacategoria_cesta(X,listacesta,C,N);
            }
           }
            break;
        case 5:
             for(int i=0;i<X.stocktienda.size();i++){
                if("Verdura"==X.stocktienda[i].categoria){
                    cout<<++cont<<"."<< X.stocktienda[i].alimento<<" Stock disponible: "
                        <<X.stocktienda[i].stock<<" Precio "<<X.stocktienda[i].precio<<endl;
                    tiendacategoria_cesta(X,listacesta,C,N);
            }
           }
            break;
        case 6:
             for(int i=0;i<X.stocktienda.size();i++){
                if("Cereales"==X.stocktienda[i].categoria){
                    cout<<++cont<<"."<< X.stocktienda[i].alimento<<" Stock disponible: "
                        <<X.stocktienda[i].stock<<" Precio "<<X.stocktienda[i].precio<<endl;
                    tiendacategoria_cesta(X,listacesta,C,N);
            }
           }
        case 7:
            break;
    }
}

void confirmarpedido(vector<cesta> listacesta, vector<cesta> historial, tienda& X, nevera A, int indice){
    char con;
    string nombre;
    cout<<"¿Quieres confirmar la compra? (s/n)" <<endl;
    cin>>con;
    if(con=='s'){
        for(int i=0; i<listacesta.size(); i++){
            historial.push_back(listacesta[i]);
            for(int k=0; k<X.stocktienda.size(); k++){
                if(listacesta[i].nombre == X.stocktienda[k].alimento){
                    X.stocktienda[k].stock -= listacesta[i].cantidad;
                }
            }
        }
        for(int i=0; i<A.enlanevera.size(); i++){
            for(int k=0; k<listacesta.size(); k++){
                if(A.enlanevera[i].alimento == listacesta[k].nombre){
                    A.enlanevera[i].stock += listacesta[k].cantidad;
                }
            }
        }
        listacesta.clear();
    }else{
        cout<<"1. Volver al menu" <<endl
        <<"2. Borrar la cesta i volver al menu principal" <<endl;
        int N;
        cin>>N;
        switch(N){
            case 1:
                menuprincipal (N);
                break;
            case 2:
                listacesta.clear();
                menuprincipal (N);
                break;
        }
    }
}

void tiendacategoria_cesta(tienda X, vector<cesta> listacesta, cesta C,int N, bool pref){
    string nom;
    cout<<"introduce el nombre del producto "<<endl;
    cin>>nom;
    for(int i=0;i<X.stocktienda.size();i++){
        if(nom==X.stocktienda[i].alimento){
            C.nombre=X.stocktienda[i].alimento;
            cout<<"Cuantos quieres?"<<endl;
            cin>>C.cantidad;
            listacesta.push_back(C);
        }else{
            cout<<"Error";
            menucategorias(N, X, listacesta, C, pref);
        }
    }
}

void menudietas(int &N, tienda X,vector<cesta> listacesta,cesta C){
int cont=0;

    cout<<"------------------------------------------------------" <<endl;
    cout<<"1. Vegano" <<endl
    <<"2. Celiacos" <<endl
    <<"3. Vegetariano" <<endl
    <<"4. Volver" <<endl;
    switch (N){
        case 1:
           for(int i=0;i<X.stocktienda.size();i++){
                if("Fruta"==X.stocktienda[i].categoria or "Verdura"==X.stocktienda[i].categoria
                   or "Cereales"==X.stocktienda[i].categoria){
                    cout<<++cont<<"."<< X.stocktienda[i].alimento<<" Stock disponible: "
                        <<X.stocktienda[i].stock<<" Precio "<<X.stocktienda[i].precio<<endl;
                    tiendacategoria_cesta(X,listacesta,C,N);
                }
           }
            break;
        case 2:
             for(int i=0;i<X.stocktienda.size();i++){
                if("Cereales"!=X.stocktienda[i].categoria ){
                    cout<<++cont<<"."<< X.stocktienda[i].alimento<<" Stock disponible: "
                    <<X.stocktienda[i].stock<<" Precio "<<X.stocktienda[i].precio<<endl;
                    tiendacategoria_cesta(X,listacesta,C,N);
            }
           }
            break;
        case 3:
             for(int i=0;i<X.stocktienda.size();i++){
                if("Pescado"!=X.stocktienda[i].categoria or "Carne"!=X.stocktienda[i].categoria){
                    cout<<++cont<<"."<< X.stocktienda[i].alimento<<" Stock disponible: "
                    <<X.stocktienda[i].stock<<" Precio "<<X.stocktienda[i].precio<<endl;
                    tiendacategoria_cesta(X,listacesta,C,N);
            }
           }
            break;


        case 6:
            break;
    }
}

void sign_in (vector<nevera> listaneveras, nevera& A, int& indice, int N){
    indice = -1; //si el programa no encuetra el usuario devuelve un -1 de indice.
    cout<<"¿Qué quieres hacer? " <<endl
    <<"1. Entrar con mi cuenta" <<endl
    <<"2. Registrarme" <<endl
    <<"3. Salir del programa" <<endl;
    cin>>N;
    switch (N){
        case 1:
            cout<<"-----------------------------------------------" <<endl;
            cout<<"introduce el nombre de usuario: ";
            cin>>A.usuario;
            cout<<"introduce la constrasena: ";
            cin>>A.contrasena;
            for(int i=0; i<listaneveras.size(); i++){
                if(A.usuario==listaneveras[i].usuario and A.contrasena==listaneveras[i].contrasena){
                    indice=i; //sino encuetra la usuario no cambiará el indice.
                }
            }
            break;
        case 2:
            cout<<"----------------------------------------------" <<endl;
            cout<<"introduce el nombre de usuario: ";
            cin>>A.usuario;
            cout<<"introduce la constrasena: ";
            cin>>A.contrasena;
            listaneveras.push_back(A);
            indice = listaneveras.size();
            break;
        case 3:
            //mirar opcion para cerrar el programa desde un void. return 0 no sirve.
            break;
    }
}

int main(){
    int N, indice, tindice; //indice para posicion del usuario y tindice para posicion de la tienda
    nevera A;
    tienda X;
    bool pref = false;
    sign_in(listaneveras, A, indice, N);
    if(indice == -1){
        sign_in(listaneveras, A, indice, N); //si no encutra nada, repite.
    }else{
        //si encuentra o se registra el usuario el programa continua aquí.
        menuprincipal(N);
        switch (N){
        case 1:
            menuusuario(N, A);
            break;
        case 2:
            comidanevera(A);
            break;
        case 3:
            //comdia tienda.
            break;
        case 4:
            return 0;
            break;
    }
    }


   /*
    switch (N){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            return 0;
            break;
    }
*/


  /*  ifstream texto ("texto.txt");
    if(texto.is_open()){
        getline(texto, s);
        //lee una linia y la mete en la variable s.
    }
    texto.close(); */

    /*switch (N){
        case 1:
            break;
        case 2:
            break;
    */
}
