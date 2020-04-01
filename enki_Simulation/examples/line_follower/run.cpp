/*
    Enki - a fast 2D robot simulator
    Copyright (C) 2017 Bernd Porr <mail@berndporr.me.uk>
    Copyright (C) 1999-2016 Stephane Magnenat <stephane at magnenat dot net>
    Copyright (C) 2004-2005 Markus Waibel <markus dot waibel at epfl dot ch>
    Copyright (c) 2004-2005 Antoine Beyeler <abeyeler at ab-ware dot com>
    Copyright (C) 2005-2006 Laboratory of Intelligent Systems, EPFL, Lausanne
    Copyright (C) 2006-2008 Laboratory of Robotics Systems, EPFL, Lausanne
    See AUTHORS for details

    This program is free software; the authors of any publication 
    arising from research using this software are asked to add the 
    following reference:
    Enki - a fast 2D robot simulator
    http://home.gna.org/enki
    Stephane Magnenat <stephane at magnenat dot net>,
    Markus Waibel <markus dot waibel at epfl dot ch>
    Laboratory of Intelligent Systems, EPFL, Lausanne.

    You can redistribute this program and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
Custom Robot example which has ground sensors and follows a line
It has also a camera which looks to the front and IR sensors
*/
#include <../../enki/Enki.h>
#include <QApplication>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <iomanip>
#include "Racer.h"
#include "../../clBP/include/clbp/Neuron.h"
#include "../../clBP/include/clbp/Layer.h"
#include "../../clBP/include/clbp/Net.h"
#include "../../clBP/lib/Net.cpp"
#include "../../clBP/lib/Layer.cpp"
#include "../../clBP/lib/Neuron.cpp"
#include "bandpass.h"
#include "parameters.h"


//#define experimentSweep
#define learning
//#define reflex

using namespace Enki;
using namespace std;

double	maxx = 250;
double	maxy = 250;

int countSteps=0;
int countRuns=0;
int learningRateCount =0;

#ifdef experimentSweep
bool save = false;
#endif

#ifndef experimentSweep
bool save = true;
#endif



    int nInputs= ROW1N+ROW2N+ROW3N; //this cannot be an odd number for icoLearner
#ifdef learning
    int nPredictors=nInputs/2;
    int nFilters = NFILTERS;
#ifdef experimentSweep
    double learningRate= LEARNINGRATE;
#endif

#ifndef experimentSweep
    double learningRate= DESIREDLEARNINGRATE;
#endif
#endif

class EnkiPlayground : public EnkiWidget
{
protected:
	Racer* racer;
    double speed = SPEED;
    double prevX;
    double prevY;
    double prevA;

#ifdef learning
    Net* net;
    double* pred = NULL;
    double* diffpred = NULL;

    Bandpass*** bandpass = 0;
    double minT = MINT;
    double maxT = MAXT;
    double dampingCoeff = DAMPINGCOEFF;

    FILE** filtlog = NULL;
    FILE* predlog = NULL;
    FILE* stats = NULL;
    FILE* wlog = NULL;
#endif
    FILE* errorlog = NULL;
    FILE* fcoord = NULL;

public:
    EnkiPlayground(World *world, QWidget *parent = 0):
		EnkiWidget(world, parent)
	{
#ifdef learning
        filtlog = new FILE*[nFilters];
        filtlog[0]= fopen("fp1.tsv","wt");
        filtlog[1]= fopen("fp2.tsv","wt");
        filtlog[2]= fopen("fp3.tsv","wt");
        filtlog[3]= fopen("fp4.tsv","wt");
        filtlog[4]= fopen("fp5.tsv","wt");
        errorlog = fopen("errorLearning.tsv","wt");
        fcoord = fopen("coordLearning.tsv","wt");
        predlog = fopen("predictors.tsv","wt");
        stats = fopen("stats.tsv", "wt");
        wlog = fopen("weight_distances.tsv", "wt");

#endif
#ifdef reflex
        errorlog = fopen("errorReflex.tsv","wt");
        fcoord = fopen("coordReflex.tsv","wt");
#endif
        racer = new Racer(nInputs);
        racer->pos = Point(maxx/2 +30, maxy/2 +5); // x and y of the start point
		racer->leftSpeed = speed;
		racer->rightSpeed = speed;
        world->addObject(racer);

#ifdef learning
        racer->setPreds(ROW1P,ROW1N,ROW1S);
        racer->setPreds(ROW2P,ROW2N,ROW2S);
        racer->setPreds(ROW3P,ROW3N,ROW3S);

        bandpass = new Bandpass**[nPredictors];

        for(int i=0;i<nPredictors;i++) {
            if (bandpass != NULL) {
                bandpass[i] = new Bandpass*[nFilters];
                 double fs = 1;
                 double fmin = fs/maxT;
                 double fmax = fs/minT;
                 double df = (fmax-fmin)/((double)(nFilters-1));
                 double f = fmin;

                for(int j=0;j<nFilters;j++) {
                    bandpass[i][j] = new Bandpass();
                    bandpass[i][j]->setParameters(f,dampingCoeff);
                    f = f + df;
                    for(int k=0;k<maxT;k++) {
                        double a = 0;
                        if (k==minT) {
                            a = 1;
                        }
                        double b = bandpass[i][j]->filter(a);
                        assert(b != NAN);
                        assert(b != INFINITY);
                    }
                    bandpass[i][j]->reset();
                }
            }
        }

        int NetnInputs = nPredictors * nFilters;

        int nLayers= NLAYERS;
        int nNeurons[3]={N1,N2,N3};
        int* nNeuronsp=nNeurons;
        net = new Net(nLayers, nNeuronsp, NetnInputs);
        net->initNetwork(Neuron::W_RANDOM, Neuron::B_NONE, Neuron::Act_Sigmoid);
        net->setLearningRate(learningRate);
        cout<< "learning rate is: "<< learningRate<< " now!"<< endl;
        pred = new double[nInputs];
        diffpred = new double[nPredictors];
        fprintf(stats, "%d\n", nPredictors);
        for (int i=0; i<nLayers; i++){
            fprintf(stats, "%d\n", nNeurons[i]);
        }
#endif
    }

    ~EnkiPlayground(){
        fclose(fcoord);
        fclose(errorlog);
#ifdef learning
        fclose(stats);
        fclose(predlog);
        fclose(filtlog[0]);
        fclose(filtlog[1]);
        fclose(filtlog[2]);
        fclose(filtlog[3]);
        fclose(filtlog[4]);
        delete[] pred;
        delete[] diffpred;
#endif

    }
	// here we do all the behavioural computations
	// as an example: line following and obstacle avoidance



virtual void sceneCompletedHook()
	{
        int errorGain = ERRORGAIN;

		double leftGround = racer->groundSensorLeft.getValue();
		double rightGround = racer->groundSensorRight.getValue();
        double error = (leftGround - rightGround);

#ifdef learning
        if (learningRate == DESIREDLEARNINGRATE && save == true){
            //cout<< "Saving the POSITIONS with learning rate: " << learningRate <<endl;
            fprintf(fcoord,"%e\t%e\n",racer->pos.x,racer->pos.y);
        }
#endif
#ifdef reflex
        if (countRuns==0){
            fprintf(fcoord,"%e\t%e\n",racer->pos.x,racer->pos.y);
        }
#endif
        fprintf(errorlog, "%e\t", error);
        error = error * errorGain;

#ifdef reflex
        racer->leftSpeed  = speed + error;
        racer->rightSpeed = speed - error;
#endif

#ifdef learning
        int predGain = PREDGAIN;
        for(int i=0; i<nInputs; i++) {
            pred[i] = (racer->groundSensorArray[i]->getValue()); //getSensorArrayValue(i);
            // workaround of a bug in Enki
//            cout<<"PRED value is: "<<pred[i]<<endl;
            //if (pred[i]<0) pred[i] = 0;
            //if (i>=racer->getNsensors()/2) fprintf(stderr,"%e ",pred[i]);
        }

        /* using the difference of the two predictors as the input: */
        for (int i=0; i<ROW1N/2; i++){
            diffpred[i]=(pred[ROW1N-1-i]-pred[i]);
        }
        for (int i=0; i<ROW2N/2; i++){
            diffpred[i+ROW1N/2]= (pred[ROW2N+ROW1N-1-i]-pred[i+ROW1N]);
        }
        for (int i=0; i<ROW3N/2; i++){
            diffpred[i+ROW1N/2+ROW2N/2]= (pred[ROW3N+ROW2N+ROW1N-1-i]-pred[i+ROW1N+ROW2N]);
        }
        if (learningRate == DESIREDLEARNINGRATE && save == true){
            //cout<< "Saving the PREDICTORS with learning rate: " << learningRate <<endl;
            for(int i=0; i<nPredictors; i++) {
                fprintf(predlog,"%e\t",diffpred[i]);
            }
            fprintf(predlog,"\n");
        }
        double pred_filtered[nPredictors][nFilters];
        for (int i=0; i<nPredictors; i++){
            for (int j=0; j<nFilters; j++){
                pred_filtered[i][j]=bandpass[i][j]->filter(diffpred[i]);
                if (learningRate == DESIREDLEARNINGRATE && save == true){
                    fprintf(filtlog[j],"%e\t",pred_filtered[i][j]);
                }

                pred_filtered[i][j]= predGain * pred_filtered[i][j];
            }
        }
        if (learningRate == DESIREDLEARNINGRATE && save == true){
            //cout<< "Saving the FILTERS with learning rate: " << learningRate <<endl;
            for (int i=0; i<nFilters; i++){
                fprintf(filtlog[i],"\n");
            }
        }
        double* pred_pointer= pred_filtered[0];
        int Netgain=NETWORKGAIN;
        net->setInputs(pred_pointer);
        net->propInputs();
        double leadError=error;
        //net->setError(leadError);
        //net->propError();
        //net->setErrorAtInput(leadError);
        net->propErrorForward();
        net->updateWeights();
        for (int i = 0; i <NLAYERS; i++){
          fprintf(wlog, "%e\t", net->getLayerWeightDistance(i));
        }
        fprintf(wlog, "%e\n", net->getWeightDistance());

        if (learningRate== DESIREDLEARNINGRATE && save == true){
            //cout<< "Saving the WEIGHTS with learning rate: " << learningRate <<endl;
            //net->saveWeights();
            //fprintf(wlog, "%e\t%e\t%e\n", weightDistance1,weightDistance2,weightDistance3);
        }
        double Output= net->getOutput(0);
        double error2 = error + Output * Netgain;
        racer->leftSpeed  = speed + error2;
        racer->rightSpeed = speed - error2;
#endif

#ifdef experimentSweep
        countSteps ++;
        if (countSteps == STEPSCOUNT){
            //cout << save << endl;
            save = false;
            countSteps =0;
            fprintf(errorlog, "\n");
            countRuns ++;
            racer->pos = Point(maxx/2 +30, maxy/2 +5);
            racer->angle=0;
            racer->leftSpeed = speed;
            racer->rightSpeed = speed;
#ifdef learning
            net->initNetwork(Neuron::W_RANDOM, Neuron::B_NONE, Neuron::Act_Sigmoid);
#endif
            if (countRuns == RUNSCOUNT){
#ifdef learning
                countRuns =0;
                learningRateCount ++;
                learningRate = learningRate / 10;
                net->setLearningRate(learningRate);
                cout<< "learning rate is: "<< learningRate<< " now!"<< endl;
                if (learningRate == DESIREDLEARNINGRATE){
                    save = true;
                    cout<< "Saving now" <<endl;
                }
                if (learningRateCount == LEARNINGRATECOUNT){
                    qApp->quit();
                }

#endif
#ifdef reflex
                qApp->quit();
#endif
            }
        }
#endif
	}
};

int main(int argc, char *argv[])
{
    srand(5);
    QApplication app(argc, argv);
    QImage gt;
    gt = QGLWidget::convertToGLFormat(QImage("cc.png"));
    if (gt.isNull()) {
        fprintf(stderr,"Texture file not found\n");
        exit(1);
    }
    const uint32_t *bits = (const uint32_t*)gt.constBits();
    World world(maxx, maxy,
                Color(1000, 1000, 1000), World::GroundTexture(gt.width(), gt.height(), bits));
    cout<<gt.width()<<" "<<gt.height()<<endl;
    EnkiPlayground viewer(&world);
    viewer.show();
    return app.exec();
}
