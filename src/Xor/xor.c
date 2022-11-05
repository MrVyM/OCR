#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Xor/function.h"
#include <stdlib.h>


Matrix* useNetwork(NeuralNetwork* net,float (*activ)(float), float a, float b)
{
	Matrix* a0 = initMatrix(1,2);
    a0->value[0][0] = a;
    a0->value[1][0] = b;    
    Matrix* z1 = mulMatrix(net->hidden,a0);
 	Matrix* a1 = applyFunctionMatrix(z1,activ);
	Matrix* z2 = mulMatrix(net->output,a1);    
	addMatrix(z2,net->outputBias);    
	Matrix* a2 = applyFunctionMatrix(z2,activ);
	return a2;
}

void showResult(NeuralNetwork* net, float (*activ)(float))
{
	printf("Result : \n");
	for(int i = 0; i <= 1; i++)
		for(int j = 0; j <=1; j++)
			printf("%d %d %f\n",i,j,(useNetwork(net,activ,i,j))->value[0][0]);
}

NeuralNetwork* trainXor(NeuralNetwork* net, float (*activ)(float),float (*deriv)(float))
{
	float learning_rate = 0.1;
	int max_iter = 5000;
	float training_set = 4.0;
    float training_list[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    float training_soluce[4][1] = {{0},{1},{1},{0}};

	Matrix* dW1 = NULL;
	Matrix* dW2 = NULL;

	Matrix* dB1 = NULL;
	Matrix* dB2 = NULL;

	Matrix* z1;
	Matrix* z2;
	
	for(int i = 0; i < max_iter; i++)
	{

	    dW1 = NULL;
	    dW2 = NULL;

	    dB1 = NULL;
	    dB2 = NULL;

	    for(int j = 0; j < training_set; j++)
		{
	        // Forward Prop.
            Matrix* a0 = initMatrix(1,2);
            a0->value[0][0] = training_list[j][0];
            a0->value[1][0] = training_list[j][1];
            z1 = mulMatrix(net->hidden,a0);
            z1 = addMatrix(z1,net->hiddenBias);
 	        Matrix* a1 = applyFunctionMatrix(z1,activ);

			z2 = mulMatrix(net->output,a1);
	        z2 = addMatrix(z2,net->outputBias);
	        Matrix* a2 = applyFunctionMatrix(z2,activ);
	        
	        // Backward Prop

	        Matrix* dz2 = addScalarMatrix(a2,-training_soluce[j][0]);
	        dW2 = addMatrix(dW2,mulMatrix(dz2,transpose(a1))); 
	        Matrix* dz1 = multiplyMatrix(mulMatrix(transpose(net->output),dz2), applyFunctionMatrix(a1, deriv));
	        dW1 = addMatrix(dW1,mulMatrix(dz1,transpose(a0)));
	        dB1 = addMatrix(dB1,dz1);
	        dB2 = addMatrix(dB2,dz2);
	    }
	    net->hidden = subMatrix(net->hidden,mulScalarMatrix(mulScalarMatrix(dW1, 1 / training_set),learning_rate));
	    net->output = subMatrix(net->output,mulScalarMatrix(mulScalarMatrix(dW2, 1 / training_set),learning_rate));
	    //printMatrix(W2);
	    net->hiddenBias = subMatrix(net->hiddenBias,mulScalarMatrix(mulScalarMatrix(dB1, 1 / training_set),learning_rate));
	    net->outputBias = subMatrix(net->outputBias,mulScalarMatrix(mulScalarMatrix(dB2, 1 / training_set),learning_rate));
	    //showResult(net,activ);
	}
    /*
	printMatrix(z1);
	printMatrix(z2);
	printf("ttest");
    */
    //printNeural(net);
    printf("Fin train\n");
    return net;
}
