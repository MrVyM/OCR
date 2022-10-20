#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Xor/function.h"
#include <stdlib.h>

NeuralNetwork* trainXor(NeuralNetwork* net, float (*activ)(float),float (*deriv)(float))
{
	int learning_rate = 0.1;
	int max_iter = 3500;
	int training_set = 4;
    printNeural(net);
    float training_list[4][2] = {{1,4},{0,1},{1,0},{1,1}};
    float training_soluce[4][1] = {{0},{1},{1},{1}};

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

 	        Matrix* a1 = applyFunctionMatrix(z1,activ);
			z2 = mulMatrix(net->output,a1);
	        addMatrix(z2,net->outputBias);
	        Matrix* a2 = applyFunctionMatrix(z2,activ);
	        
	        Matrix* dz2 = addScalarMatrix(a2,-training_soluce[j][0]);
	        dW2 = addMatrix(dW2,mulMatrix(dz2,transpose(a1))); 
	        Matrix* dz1 = multiplyMatrix(mulMatrix(transpose(net->output),a2), applyFunctionMatrix(a1, deriv));
	        dW1 = addMatrix(dW1,mulMatrix(dz1,transpose(a0)));
	        dB1 = addMatrix(dB1,dz1); 
	        dB2 = addMatrix(dB2,a2);
	        printf("Fin boucle trainning\n");
	    }
	    printf("fin boucle\n");
	    addScalarMatrix(net->hidden, - learning_rate);
	    mulScalarMatrix(dW1,1 / training_set);
	    printMatrix(dW1);
	    printMatrix(net->hidden);
	    net->hidden = mulMatrix(net->hidden,dW1);
	    printf("hidden\n");
	    addScalarMatrix(net->output, - learning_rate);
	    
	    mulScalarMatrix(dW2,1 / training_set);
	    net->output = mulMatrix(net->output,dW2);

	    printf("Bias\n");

	    addScalarMatrix(net->hiddenBias, - learning_rate);
	    mulScalarMatrix(dB1,1 / training_set);
	    net->hiddenBias = mulMatrix(net->hiddenBias,dB1);
	    addScalarMatrix(net->outputBias, - learning_rate);
	    mulScalarMatrix(dB2,1 / training_set);
	    net->outputBias = mulMatrix(net->outputBias,dB2);
	}
    /*
	printMatrix(z1);
	printMatrix(z2);
	printf("ttest");
    */
    printf("Fin train\n");
    return net;
}
