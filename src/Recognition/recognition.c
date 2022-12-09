#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Xor/function.h"
#include "Input/file.h"
#include <stdlib.h>
#include <err.h>


Matrix* recognized(NeuralNetwork* net,float (*activ)(float), Matrix* input)
{
    /*
    Matrix* z0 = addMatrix(mulMatrix(net->hidden1, input), net->hidden1Bias);
    Matrix* a0 = applyFunctionMatrix(z0, activ);
    Matrix* z1 = addMatrix(mulMatrix(net->hidden2, a0), net->hidden2Bias);
    Matrix* a1 = applyFunctionMatrix(z1, activ);
    Matrix* z2 = addMatrix(mulMatrix(net->output, a1), net->outputBias);
    Matrix* a2 = applyFunctionMatrix(z2, activ);
    return a2;*/
    //Zh1 = [ X • wh1 ] + bh1
    Matrix* Zh1 = addMatrix(mulMatrix(net->hidden1, input), net->hidden1Bias);

    //ah1 = Φ (Zh1)
    Matrix* ah1 = applyFunctionMatrix(Zh1, activ);

    //Zh2 = [ ah1 • wh2 ] + bh2
    Matrix* Zh2 = addMatrix(mulMatrix(net->hidden2, ah1), net->hidden2Bias);

    // ah2 = Φ (Zh2)
    Matrix* ah2 = applyFunctionMatrix(Zh2, activ);

    // Zout = [ ah2 • wout ] + bhout
    Matrix* Zout = addMatrix(mulMatrix(net->output, ah2), net->outputBias);

    // aout = Φ (Zout)
    Matrix* aout = applyFunctionMatrix(Zout, activ);


    freeMatrix(Zh1);
    freeMatrix(ah1);
    freeMatrix(Zh2);
    freeMatrix(ah2);
    freeMatrix(Zout);
    return aout;
}


void showStat(NeuralNetwork* net, float (*activ)(float))
{
    FILE* lines = fopen("assets/Test/lines.txt", "r");
    if (lines == NULL)
        errx(-1, "showStat : Cannot read the lines\n");
    float line = (float)readNumber(lines);
    // printf("Load the number of lines(%f)\n",line);
    fclose(lines);

    Matrix* training_list = readData("assets/Test/data.txt", line);
    Matrix* input = initMatrix(1,784);
    float ratio = 0.0;
    int tested =0;
    for(int height = 0; height < line; height++)
    {
        for(int h = 0; h < 784; h++)
            input->value[h][0] = training_list->value[height][h];
        if ((int)(training_list->value[height][784]) != 0)
        {
            tested ++;
            int result = maxIndexMatrix(recognized(net,sigmoid,input));
            if ((int)(training_list->value[height][784]) == result)
                ratio+= 1.0;
            else
            {
                printf("\tS : %d \t R : %d\n",(int)(training_list->value[height][784]), result);
            }
        }
        // printf("The result : %d\n",result);
    }
    printf("\nRatio : %f\n\n", (ratio/line)*100);
}

Matrix* costFunction(Matrix* soluce, Matrix* result)
{
    float t = 0;
    Matrix* res = initMatrix(1,soluce->height);
    for(int i = 0; i < soluce->height; i++)
    {   
        t = (result->value[0][i] - soluce->value[0][i]);
        res->value[0][i] = t*t;
    }
    return mulScalarMatrix(res,1/2);
}

NeuralNetwork* trainRecognition(NeuralNetwork* net, float (*activ)(float),float (*deriv)(float))
{
    //printNeural(net);
    float learning_rate = 0.001;
    int max_iter = 10;

    FILE* lines = fopen("assets/Dataset/lines.txt", "r");
    // printf("Load the number of lines\n");
    float training_set = (float)readNumber(lines);
    fclose(lines);
    // printf("training_set : %f\n", training_set);
    Matrix* training_list = readData("assets/Dataset/data.txt", training_set);
    // printf("Load the dataset\n");

    Matrix* input = initMatrix(1,784);
    Matrix** list_soluce = malloc(sizeof(struct Matrix) * 10);

    for(int i = 0; i < 10; i++)
    {
        list_soluce[i] = initMatrix(1,10);
        list_soluce[i]->value[i][0] = 1.0;
    }
    Matrix* soluce;

    float train_v = 0;
    float train_f = 0;
    float bhd = 0;

    for(int i = 0; i < max_iter; i++)
    {
        for(int high = 0; high < training_set; high++)
        {
            int rng = (int)(rand());
            int j = (high+rng)%(int)training_set;
            for(int h = 0; h < 784; h++)
                input->value[h][0] = training_list->value[j][h];

            Matrix* Zh1;
            Matrix* ah1;
            Matrix* Zh2;
            Matrix* ah2;
            Matrix* Zout;
            Matrix* aout;

            Matrix* Errorout;
            Matrix* ah2T;
            Matrix* deltaWout;
            Matrix* deltaBout;
            Matrix* wouT;
            Matrix* Error2;
            Matrix* ah1T;
            Matrix* deltaWh2;
            Matrix* deltaBh2;
            Matrix* wh2T;
            Matrix* Error3;    
            Matrix* XT;
            Matrix* deltaWh1; 
            Matrix* deltaBh1;
            soluce = list_soluce[(int)(training_list->value[j][784])];
            // printf("Soluce : %d\n",(int)(training_list->value[j][784]));
            // Forward Propagation

            //Zh1 = [ X • wh1 ] + bh1
            Zh1 = addMatrix(mulMatrix(net->hidden1, input), net->hidden1Bias);

            //ah1 = Φ (Zh1)
            
            ah1 = applyFunctionMatrix(Zh1, activ);

            //Zh2 = [ ah1 • wh2 ] + bh2
            Zh2 = addMatrix(mulMatrix(net->hidden2, ah1), net->hidden2Bias);

            // ah2 = Φ (Zh2)
            ah2 = applyFunctionMatrix(Zh2, activ);

            // Zout = [ ah2 • wout ] + bhout
            Zout = addMatrix(mulMatrix(net->output, ah2), net->outputBias);

            // aout = Φ (Zout)
            aout = applyFunctionMatrix(Zout, activ);
            
            
            // Backward Propagation

            // Step 1:
            // Errorout = aout - soluce
            Errorout = subMatrix(aout, soluce);

            //Step 2:
            // Δwout = η ( ah2T • Errorout ) (η -> learning rate)
            ah2T = transpose(ah2);
            deltaWout = mulScalarMatrix(mulMatrix(Errorout, ah2T), learning_rate);

            // Δbout = η [ ∑i=1,n (Errorout,i) ]
            deltaBout = mulScalarMatrix(Errorout, learning_rate);

            // Update weight ant bias
            // wout = wout - Δwout
            net->output = subMatrix(net->output, deltaWout);

            // bout = bout - Δbout
            net->outputBias = subMatrix(net->outputBias, deltaBout);

            // Step 3:
            // Error2 = [Errorout • woutT] ✴ Φ/ (ah2) (Φ/ -> derivative of sigmoid function)
            wouT = transpose(net->output);
            Error2 = multiplyMatrix(mulMatrix(wouT, Errorout), applyFunctionMatrix(ah2, deriv));

            // Step 4:
            // Δwh2 = η ( ah1T • Error2 )
            ah1T = transpose(ah1);
            deltaWh2 = mulScalarMatrix(mulMatrix(Error2, ah1T), learning_rate);

            // Δbh2 = η [∑ i=1n (Error2,i)]
            deltaBh2 = mulScalarMatrix(Error2, learning_rate);

            // Update weight ant bias
            // wh2 = wh2 - Δwh2
            net->hidden2 = subMatrix(net->hidden2, deltaWh2);

            // bh2 = bh2 - Δbh2
            net->hidden2Bias = subMatrix(net->hidden2Bias, deltaBh2);

            // Step 5:
            // Error2 = [Error2 • wh2T] ✴ Φ/ (ah1)
            wh2T = transpose(net->hidden2);
            Error3 = multiplyMatrix(mulMatrix(wh2T, Error2), applyFunctionMatrix(ah1, deriv));

            // Step 6:
            // Δwh1 = η ( XT • Error3 )
            XT = transpose(input);
            deltaWh1 = mulScalarMatrix(mulMatrix(Error3, XT), learning_rate);

            // Δbh1 = η [∑ i=1n (Error3,i)]
            deltaBh1 = mulScalarMatrix(Error3, learning_rate);

            // Update weight ant bias
            // wh1 = wh1 - Δwh1
            net->hidden1 = subMatrix(net->hidden1, deltaWh1);

            // bh1 = bh1 - Δbh1
            net->hidden2Bias = subMatrix(net->hidden1Bias, deltaBh1);

            Matrix* p = recognized(net, activ, input);
            if(maxIndexMatrix(p) == maxIndexMatrix(soluce))
            {
                train_v += 1;
            }
            else
            {
                train_f += 1;
            }

        freeMatrix(Zh1);
        freeMatrix(ah1);
        freeMatrix(Zh2);
        freeMatrix(ah2);
        freeMatrix(Zout);
        freeMatrix(aout);

        freeMatrix(Errorout);
        freeMatrix(ah2T);
        freeMatrix(deltaWout);
        freeMatrix(deltaBout);
        freeMatrix(wouT);
        freeMatrix(Error2);
        freeMatrix(ah1T);
        freeMatrix(deltaWh2);
        freeMatrix(deltaBh2);
        freeMatrix(wh2T);
        freeMatrix(Error3);    
        freeMatrix(XT);
        freeMatrix(deltaWh1); 
        freeMatrix(deltaBh1);
        }
    }

    bhd = train_v / (train_v + train_f);
    printf("Ratio Data : %f\n\n", bhd*100);
    freeMatrix(input);
    return net;
}
