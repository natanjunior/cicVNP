#include "Arquivo.h"

#include <QDebug>

using namespace std;

Arquivo::Arquivo(string arq) {
    enderecoArq = arq;
}

void Arquivo::lerArquivo(Modelo *md){
    size_t found = enderecoArq.find_last_of("/\\");
    string nomeArquivo = enderecoArq.substr(found+1);
    string formatoArquivo = nomeArquivo.substr(nomeArquivo.size()-4,4);

    modelo = md;

    modelo->setNome(nomeArquivo);

    if(formatoArquivo.compare(".txt")==0){
        parserPadrao();
        modelo->setFormato(0);      // PADRAO
    }else if(formatoArquivo.compare(".ply")==0){
        parserPly();
        modelo->setFormato(1);      // PLY
    }else if(formatoArquivo.compare(".pts")==0){
        parserPts();
        modelo->setFormato(2);      // PTS
    }
}

void Arquivo::lerArquivo(Video *video){
    size_t found = enderecoArq.find_last_of("/\\");
    string nomeArquivo = enderecoArq.substr(found+1);
    //    string formatoArquivo = nomeArquivo.substr(nomeArquivo.size()-4,4);

    video->setNome(nomeArquivo);

    parserVideo(video);
}

vector<string> Arquivo::split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

void Arquivo::parserPadrao(){
    string linha;
    int y, u, v;
    float x_max = 0, y_max = 0, z_max = 0;  // min para o padrão
    float x_min = 512, y_min = 512, z_min = 512;  // max para o padrão

    ifstream myfile (enderecoArq);
    if (myfile.is_open()){
        while (! myfile.eof() ){
            getline (myfile,linha);
            vector<string> vLinha = split(linha, ' ');
            if(vLinha.size()==6){ // no parse padrão podemos garantir isso
                try{
//                    x_coord = (stof(vLinha[0])/512)-0.5;
//                    y_coord = (stof(vLinha[1])/512)-0.5;
//                    z_coord = (stof(vLinha[2])/512)-0.5;
                    x_coord = stof(vLinha[0]);
                    y_coord = stof(vLinha[1]);
                    z_coord = stof(vLinha[2]);

                    y = stoi(vLinha[3]);
                    u = stoi(vLinha[4]);
                    v = stoi(vLinha[5]);

                    r = (char) abs((1.164 * (y - 16)) + (1.596 * (v - 128))); // cast yuv to r
                    g = (char) abs((1.164 * (y - 16)) - (0.813 * (v - 128)) - (0.391 * (u - 128))); // cast yuv to g
                    b = (char) abs((1.164 * (y - 16)) + (2.018 * (u - 128))); // cast yuv to b
                }catch(exception& e){
                    qDebug() << e.what();
                }

                Voxel ponto = *new Voxel(x_coord, y_coord, z_coord, r, g, b);

                modelo->addPonto(ponto);

                x_max = max(x_max, x_coord);
                x_min = min(x_min, x_coord);
                y_max = max(y_max, y_coord);
                y_min = min(y_min, y_coord);
                z_max = max(z_max, z_coord);
                z_min = min(z_min, z_coord);
            }
        }
        modelo->setDimensoes(x_max, y_max, z_max, x_min, y_min, z_min);
    }
    myfile.close();
}

int point_cb(p_ply_argument argument) {
    Arquivo::CallbackContext *context;
    long eol, value;
    p_ply_property propriedade;
    const char* nome;
    ply_get_argument_user_data(argument, (void **)&context, &eol);
    ply_get_argument_property(argument, &propriedade, NULL, NULL);
    ply_get_property_info(propriedade, &nome, NULL, NULL, NULL);
    ply_get_argument_element(argument, NULL, &value);
    if(strcmp(nome,"x")==0) context->ponto->setX_coord(ply_get_argument_value(argument));
    else if(strcmp(nome,"y")==0) context->ponto->setY_coord(ply_get_argument_value(argument));
    else if(strcmp(nome,"z")==0) context->ponto->setZ_coord(ply_get_argument_value(argument));
    else if(strcmp(nome,"red")==0) context->ponto->setR_color((char) ply_get_argument_value(argument));
    else if(strcmp(nome,"green")==0) context->ponto->setG_color((char) ply_get_argument_value(argument));
    else if(strcmp(nome,"blue")==0) context->ponto->setB_color((char) ply_get_argument_value(argument));
    if (eol == 0){
        context->modelo->addPonto(* context->ponto);
        context->ponto = new Voxel();
        return 2;
    }
    return 1;
}

void Arquivo::parserPly(){
    p_ply ply = ply_open(enderecoArq.c_str(), NULL, 0, NULL);
    if (!ply) return;                                 // verifica se é um arquivo PLY
    if (!ply_read_header(ply)) return;                // verifica o cabeçalho

    long qtndPontos = 0;

    QList<QString> listaPropriedades;

    p_ply_element elemento = NULL;
    p_ply_property propriedade = NULL;
    while ((elemento = ply_get_next_element(ply, elemento)) != NULL) {
        const char *nome;

        ply_get_element_info(elemento, &nome, &qtndPontos);
        if (strcmp(nome, "vertex")==0){
            while ((propriedade = ply_get_next_property(elemento, propriedade)) != NULL) {
                const char *nomePropriedade;
                ply_get_property_info(propriedade, &nomePropriedade, NULL, NULL, NULL);
                listaPropriedades.append(nomePropriedade);
            }
        }
    }

    if (qtndPontos == 0) return;

    CallbackContext context;
    context.ponto = new Voxel();
    context.modelo = modelo;
    for (int i = 0; i < listaPropriedades.size(); ++i) {
        ply_set_read_cb(ply, "vertex", listaPropriedades.at(i).toStdString().c_str(), point_cb, &context, listaPropriedades.size()-(i+1));
    }
    if (!ply_read(ply)) return;
    ply_close(ply);
}

void Arquivo::parserPts(){
    string linha;
    float x_max = numeric_limits<float>::min(), y_max = numeric_limits<float>::min(), z_max = numeric_limits<float>::min();
    float x_min = numeric_limits<float>::max(), y_min = numeric_limits<float>::max(), z_min = numeric_limits<float>::max();

    ifstream myfile (enderecoArq);
    if (myfile.is_open()){
        while (! myfile.eof() ){
            getline (myfile,linha);
            vector<string> vLinha = split(linha, ' ');
            if(vLinha.size()>=6){

                try{
                    x_coord = stof(vLinha[0]);
                    y_coord = stof(vLinha[1]);
                    z_coord = stof(vLinha[2]);

                    r = (char) stoi(vLinha[3]);
                    g = (char) stoi(vLinha[4]);
                    b = (char) stoi(vLinha[5]);
                }catch(exception& e){
                    qDebug() << e.what();
                }

                Voxel ponto = *new Voxel(x_coord, y_coord, z_coord, r, g, b);

                x_max = max(x_max, x_coord);
                x_min = min(x_min, x_coord);
                y_max = max(y_max, y_coord);
                y_min = min(y_min, y_coord);
                z_max = max(z_max, z_coord);
                z_min = min(z_min, z_coord);

                modelo->addPonto(ponto);
            }
        }
        modelo->setDimensoes(x_max, y_max, z_max, x_min, y_min, z_min);
    }
    myfile.close();
}

void Arquivo::parserVideo(Video *video){
    string linha;
    vector<Voxel> pontos;
    vector< vector<Voxel> > frames;
    float x_coord, y_coord, z_coord, r, g, b;

    ifstream myfile (enderecoArq);
    if (myfile.is_open()){
        while (! myfile.eof() ){
            getline (myfile,linha);
            vector<string> vLinha = split(linha, ' ');
            if((linha.compare("new_frame")==0)||(linha.compare("new_frame\r")==0)){
                frames.push_back(pontos);
                pontos.clear();
            }else if(vLinha.size()>2){  // temp, mudar apos definicao
                try{
                    x_coord = stof(vLinha[0]);
                    y_coord = stof(vLinha[1]);
                    z_coord = stof(vLinha[2]);

                    r = (char) stoi(vLinha[3]);
                    g = (char) stoi(vLinha[4]);
                    b = (char) stoi(vLinha[5]);
                }catch(exception& e){
                    qDebug() << e.what();
                }

                Voxel ponto = *new Voxel(x_coord, y_coord, z_coord, r, g, b);

                pontos.push_back(ponto);
            }
        }
        video->setFrames(frames);
    }
}

void Arquivo::salvarArquivo(string fileName, Modelo *modelo){
    size_t found = fileName.find_last_of("/\\");
    string nomeArquivo = fileName.substr(found+1);
    string formatoArquivo = nomeArquivo.substr(nomeArquivo.size()-4,4);

    if(formatoArquivo.compare(".ply")==0){
        escritorPly(fileName, modelo->getPontos());
    }else if(formatoArquivo.compare(".pts")==0){
        escritorPts(fileName, modelo->getPontos());
    }
}

void Arquivo::escritorPly(string fileName, vector<Voxel> *pontos){
    ofstream arq;
    arq.open(fileName);
    if (arq.is_open() && arq.good()){
        arq << "ply" << endl;
        arq << "format ascii 1.0" << endl;
        arq << "element vertex " << pontos->size() << endl;
        arq << "property float x" << endl;
        arq << "property float y" << endl;
        arq << "property float z" << endl;
        arq << "property uchar red" << endl;
        arq << "property uchar green" << endl;
        arq << "property uchar blue" << endl;
        arq << "end_header" << endl;
    }

    for (vector<Voxel>::iterator it = pontos->begin() ; it != pontos->end(); ++it){
        Voxel ponto = *it;
        arq << ponto.getLinha() << endl;
    }
}

void Arquivo::escritorPts(string fileName, vector<Voxel> *pontos){
    ofstream arq;
    arq.open(fileName);
    if (arq.is_open() && arq.good()){
        arq << "ply" << endl;
        arq << "format ascii 1.0" << endl;
        arq << "element vertex " << pontos->size() << endl;
        arq << "property float x" << endl;
        arq << "property float y" << endl;
        arq << "property float z" << endl;
        arq << "property uchar red" << endl;
        arq << "property uchar green" << endl;
        arq << "property uchar blue" << endl;
        arq << "end_header" << endl;
    }
}
