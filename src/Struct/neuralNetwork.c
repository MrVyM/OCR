#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Input/file.h"
#include <stdlib.h>
#include <err.h>
#include <string.h>

NeuralNetwork* initNetwork()
{
	NeuralNetwork* network = malloc(sizeof(NeuralNetwork));

	if (network == NULL)
		errx(-1,"NeuralNetwork cannot be initialize.");

	int num_hidden1 = 64;
	int num_hidden2 = 64; 
    network->hidden1 = randomMatrix(784,num_hidden1,1);
    network->hidden2 = randomMatrix(num_hidden1,num_hidden2,1);
	network->hidden1Bias = randomMatrix(1,num_hidden1,0);
    network->hidden2Bias = randomMatrix(1,num_hidden2,0);
	network->output = randomMatrix(num_hidden2,10,0);
	network->outputBias = randomMatrix(1,10,0);

	return network;
}

void saveWeight(char hidden1_c[], char hidden2_c[], char output_c[], NeuralNetwork* net)
{
    FILE *hidden1 = fopen(hidden1_c, "w");
    FILE *hidden2 = fopen(hidden2_c, "w");
    FILE *output = fopen(output_c, "w");

    if (hidden1 == NULL || hidden2 == NULL || output == NULL)
    {
        printf("saveWeight : Can't save the network\n");
    }
    else 
    {
        // printf("Saving the weight in %s\n",hidden1_c);
	for(size_t i = 0; i < 16; ++i)
	{
		for(size_t j = 0; j < 784; ++j)
		{
			fprintf(hidden1, "%f ", net->hidden1->value[i][j]);
		}
		fprintf(hidden1,"| ");
		for(size_t j = 0; j < 16; ++j)
		{
			fprintf(hidden1,"%f ",net->hidden1Bias->value[j][0]);
		}
		fprintf(hidden1,"\n");
	}
        // printf("Saving the weight in %s\n",hidden2_c);

	for(size_t i = 0; i < 16; ++i)
	{
		for(size_t j = 0; j < 16; ++j)
		{
			fprintf(hidden2, "%f ", net->hidden2->value[i][j]);
		}
		fprintf(hidden2,"| ");
		for(size_t j = 0; j < 16; ++j)
		{
			fprintf(hidden2,"%f ",net->hidden2Bias->value[j][0]);
		}
		fprintf(hidden2,"\n");
	}
        // printf("Saving the weight in %s\n",output_c);

	for(size_t i = 0; i < 10; ++i)
	{
		for(size_t j = 0; j < 16; ++j)
		{
			fprintf(output, "%f ", net->output->value[i][j]);
		}
		fprintf(output,"| ");
		for(size_t j = 0; j < 10; ++j)
		{
			fprintf(output,"%f ",net->output->value[j][0]);
		}
		fprintf(output,"\n");
	}
        fclose(hidden1);
        fclose(hidden2);
        fclose(output);
    }
}

NeuralNetwork* loadWeight(char hidden1_c[], char hidden2_c[], char output_c[])
{    
	FILE *hidden1 = fopen(hidden1_c, "r");
	FILE *hidden2 = fopen(hidden2_c, "r");
	FILE *output = fopen(output_c, "r");
	NeuralNetwork* net = initNetwork();
	if(net == NULL)
		errx(-1,"NeuralNetwork cannot be initialize.");

    if (hidden1 == NULL || hidden2 == NULL || output == NULL)
	{
		printf("loadWeight : Can't load the network");
		return net;
	} 
	else 
	{
		net->hidden1 = initMatrix(784,16);
		net->hidden1Bias = initMatrix(1,16);
		net->hidden2 = initMatrix(16,16);
		net->hidden2Bias = initMatrix(1,16);
		net->output = initMatrix(16,10);
		net->outputBias = initMatrix(1,10);
		for(size_t i = 0; i < 16; ++i)
		{
			for(size_t j = 0; j < 784; ++j)
			{
				net->hidden1->value[i][j] = readFloat(hidden1);
	//			printf("hidden1 -> %f\n",net->hidden1->value[i][j]);
			}
			fgetc(hidden1);
			fgetc(hidden1);
			for(size_t j = 0; j < 16; ++j)
			{
				net->hidden1Bias->value[j][0] = readFloat(hidden1);
	//			printf("hidden1Bias -> %f\n",net->hidden1Bias->value[j][0]);
			}
			fgetc(hidden1);
		}

		for(size_t i = 0; i < 16; ++i)
		{
			for(size_t j = 0; j < 16; ++j)
			{
				net->hidden2->value[i][j] = readFloat(hidden2);
//				printf("hidden2 -> %f\n",net->hidden2->value[i][j]);
			}
			fgetc(hidden2);
			fgetc(hidden2);
			for(size_t j = 0; j < 16; ++j)
			{
				net->hidden2Bias->value[j][0] = readFloat(hidden2);
	//			printf("hidden2Bias -> %f\n",net->hidden2Bias->value[j][0]);
			}
			fgetc(hidden2);
		}


		for(size_t i = 0; i < 10; ++i)
		{
			for(size_t j = 0; j < 16; ++j)
			{
				net->output->value[i][j] = readFloat(output);
	//			printf("output -> %f\n",net->output->value[i][j]);
			}
			fgetc(output);
			fgetc(output);
			for(size_t j = 0; j < 10; ++j)
			{
				net->outputBias->value[j][0] = readFloat(output);
//				printf("Bias -> %f\n",net->outputBias->value[j][0]);
			}
			fgetc(output);
		}
	}
        fclose(hidden1);
        fclose(hidden2);
        fclose(output);
	return net;
}

void printNeural(NeuralNetwork* net)
{
	printf("Hidden1 :\n");
	printMatrix(net->hidden1);
	printf("Hidden2 :\n");
	printMatrix(net->hidden2);
	printf("Output :\n");
	printMatrix(net->output);
	printf("HiddenBias1 :\n");
	printMatrix(net->hidden1Bias);
	printf("HiddenBias2 :\n");
	printMatrix(net->hidden2Bias);
	printf("OutputBias :\n");
	printMatrix(net->outputBias);
}

void freeNetwork(NeuralNetwork* network)
{
	free(network->hidden1);
	free(network->hidden2);
	free(network->output);
	free(network->hidden1Bias);
	free(network->hidden2Bias);
	free(network->outputBias);

	free(network);
}
