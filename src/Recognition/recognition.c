#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Xor/function.h"
#include "Input/file.h"
#include <stdlib.h>


Matrix* recognized(NeuralNetwork* net,float (*activ)(float), Matrix* input)
{
	Matrix* z0 = addMatrix(mulMatrix(net->hidden1, input), net->hidden1Bias);
    Matrix* a0 = applyFunctionMatrix(z0, activ);
    Matrix* z1 = addMatrix(mulMatrix(net->hidden2, a0), net->hidden2Bias);
    Matrix* a1 = applyFunctionMatrix(z1, activ);
    Matrix* z2 = addMatrix(mulMatrix(net->output, a1), net->outputBias);
    Matrix* a2 = applyFunctionMatrix(z2, activ);
    return a2;
}

void showStat(NeuralNetwork* net, float (*activ)(float))
{
	printf("Result : \n");
    /*
	for(int i = 0; i <= 1; i++)
		for(int j = 0; j <=1; j++)
			printf("%d %d %f\n",i,j,(recognized(net,activ,))->value[0][0]);
    */
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
    return res;
}

NeuralNetwork* trainRecognition(NeuralNetwork* net, float (*activ)(float),float (*deriv)(float))
{
    //printNeural(net);
	float learning_rate = 0.2;
	int max_iter = 1;
    FILE* lines = fopen("assets/Dataset/lines.txt", "r");
	float training_set = readNumber(lines);
    fclose(lines);
    Matrix* training_list = readData("assets/Dataset/data.txt", "assets/Dataset/lines.txt");

    Matrix* dZ0;
    Matrix* dZ1;
    Matrix* dZ2;

    Matrix* dB0;
    Matrix* dB1;
    Matrix* dB2;

    Matrix* input = initMatrix(1,784);
    Matrix** list_soluce = malloc(sizeof(struct Matrix) * 10);

    for(int i = 0; i < 10; i++)
    {
        list_soluce[i] = initMatrix(1,10);
        list_soluce[i]->value[0][i] = 1.0;
    }
    Matrix* soluce;

    Matrix* hidden1Tranpose = transpose(net->hidden1);
    Matrix* hidden2Tranpose = transpose(net->hidden2);
    Matrix* outputTranpose = transpose(net->output);


	for(int i = 0; i < max_iter; i++)
	{
	    for(int j = 0; j < training_set; j++)
		{
            for(int h = 0; h < 784; h++)
                input->value[h][0] = training_list->value[j][h];
            soluce = list_soluce[(int)(training_list->value[j][i])];

            // Forward Propagation

            //Zh1 = [ X • wh1 ] + bh1
            Matrix* Zh1 = addMatrix(mulMatrix(net->hidden1, input), net->hidden1Bias);
            /*
            printf("Zh1 h = %d (h1) w = %d (n)\n", Zh1->height, Zh1->width);
            printf("X h = %d (d) w = %d (n)\n", input->height, input->width);
            printf("Wh1 h = %d (h1) w = %d (d)\n", net->hidden1->height, net->hidden1->width);
            printf("bh1 h = %d (h1) w = %d (1)\n", net->hidden1Bias->height, net->hidden1Bias->width);
            */

            //ah1 = Φ (Zh1)
            Matrix* ah1 = applyFunctionMatrix(Zh1, activ);
            //Zh2 = [ ah1 • wh2 ] + bh2

            Matrix* Zh2 = addMatrix(mulMatrix(net->hidden2, ah1), net->hidden2Bias);
            // ah2 = Φ (Zh2)
            Matrix* ah2 = applyFunctionMatrix(Zh2, activ);
            // Zout = [ ah2 • wout ] + bhout

            Matrix* Zout = addMatrix(mulMatrix(net->output, ah2), net->outputBias);
            /*
            printf("\n");
            printf("Zout h = %d (t) w = %d (n)\n", Zout->height, Zout->width);
            printf("ah2 h = %d (h2) w = %d (n)\n", ah2->height, ah2->width);
            printf("wout h = %d (t) w = %d (h2)\n", net->output->height, net->output->width);
            printf("bout h = %d (t) w = %d (1)\n", net->outputBias->height, net->outputBias->width);
            */

            // aout = Φ (Zout)
            Matrix* aout = applyFunctionMatrix(Zout, activ);
            
            
            // Backward Propagation

            // Step 1:
            // Errorout = aout - soluce
            Matrix* Errorout = subMatrix(aout, soluce);
            /*
            printMatrix(Errorout);// h = 10 -
            printMatrix(aout);
            printMatrix(soluce);*/

            //Step 2:
            // Δwout = η ( ah2T • Errorout ) (η -> learning rate)
            Matrix* ah2T = transpose(ah2);
            printMatrix(ah2T); // h = 1 w = 16
            Matrix* deltaWout = mulScalarMatrix(mulMatrix(Errorout, ah2T), learning_rate);

            // Δbout = η [ ∑i=1,n (Errorout,i) ]
            Matrix * deltaBout = mulScalarMatrix(Errorout, learning_rate);

            // Update weight ant bias
            // wout = wout - Δwout
            net->output = subMatrix(net->output, deltaWout);

            // bout = bout - Δbout
            net->outputBias = subMatrix(net->outputBias, deltaBout);

            // Step 3:
            // Error2 = [Errorout • woutT] ✴ Φ/ (ah2) (Φ/ -> derivative of sigmoid function)
            Matrix* wouT = transpose(net->output);
            Matrix* Error2 = multiplyMatrix(mulMatrix(wouT, Errorout), applyFunctionMatrix(ah2, deriv));

            // Step 4:
            // Δwh2 = η ( ah1T • Error2 )
            Matrix* ah1T = transpose(ah1);
            Matrix* deltaWh2 = mulScalarMatrix(mulMatrix(Error2, ah1T), learning_rate);

            // Δbh2 = η [∑ i=1n (Error2,i)]
            Matrix* deltaBh2 = mulScalarMatrix(Error2, learning_rate);

            // Update weight ant bias
            // wh2 = wh2 - Δwh2
            net->hidden2 = subMatrix(net->hidden2, deltaWh2);

            // bh2 = bh2 - Δbh2
            net->hidden2Bias = subMatrix(net->hidden2Bias, deltaBh2);

            // Step 5:
            // Error2 = [Error2 • wh2T] ✴ Φ/ (ah1)
            Matrix* wh2T = transpose(net->hidden2);
            Matrix* Error3 = multiplyMatrix(mulMatrix(wh2T, Error2), applyFunctionMatrix(ah1, deriv));

            // Step 6:
            // Δwh1 = η ( XT • Error3 )
            Matrix* XT = transpose(input);
            Matrix* deltaWh1 = mulScalarMatrix(mulMatrix(Error3, XT), learning_rate);

            // Δbh1 = η [∑ i=1n (Error3,i)]
            Matrix* deltaBh1 = mulScalarMatrix(Error3, learning_rate);

            // Update weight ant bias
            // wh1 = wh1 - Δwh1
            net->hidden1 = subMatrix(net->hidden1, deltaWh1);

            // bh1 = bh1 - Δbh1
            net->hidden2Bias = subMatrix(net->hidden1Bias, deltaBh1);
            
            printf("%d t = %f\n",j,training_set);
	    }
        if (i % 100 == 0)
            printf("Iter : %d\n",i);
    }
    printf("pass\n");
    freeMatrix(input);
    return net;
}
