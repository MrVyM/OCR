#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Xor/function.h"

NeuralNetwork* trainXor(NeuralNetwork* net, float (*activ)(float),float (*deriv)(float))
{
	int learning_rate = 0.1;
	int max_iter = 3500;
	int training_set = 4;
    
    float training_list[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    //float training_soluce[4][1] = {{0},{1},{1},{1}};

	int dW1 = 0;
	int dW2 = 0;

	int dB1 = 0;
	int dB2 = 0;

	Matrix* z1;
	Matrix* z2;
	
	for(int i = 0; i < max_iter; i++)
	{

	    dW1 = 0;
	    dW2 = 0;

	    dB1 = 0;
	    dB2 = 0;

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

            
	        Matrix* a3 = applyFunctionMatrix(z2,activ);
	        /*
	        // Back prop.
	        Matrix* dz2 = subMatrix(a2,training_soluce[j]);
	        dW2 += mulMatrix(dz2,transpose(a1)); 

	        dz1 = np.multiply((transpose(W2) * dz2), sigmoid(a1, derivation=True))
	        dW1 += dz1.dot(transpose(a0));

	        dB1 += dz1
	        dB2 += dz2;
            */

	    }
	    addScalarMatrix(net->hidden, - learning_rate);
	    mulScalarMatrix(net->hidden,(dW1 / training_set));
	    addScalarMatrix(net->output, - learning_rate);
	    mulScalarMatrix(net->output,(dW2 / training_set));

	    addScalarMatrix(net->hiddenBias, - learning_rate);
	    mulScalarMatrix(net->hiddenBias,(dB1 / training_set));
	    addScalarMatrix(net->outputBias, - learning_rate);
	    mulScalarMatrix(net->outputBias,(dB2 / training_set));
	}
    /*
	printMatrix(z1);
	printMatrix(z2);
	printf("ttest");
    */
    return net;
}
