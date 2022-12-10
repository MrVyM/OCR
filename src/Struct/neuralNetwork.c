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

	int num_hidden1 = 25;
	int num_hidden2 = 25; 
    network->hidden1 = randomMatrix(784,num_hidden1,1);
    network->hidden2 = randomMatrix(num_hidden2,num_hidden1,1);
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
	for(int i = 0; i < net->hidden1->height; ++i)
	{
		for(int j = 0; j < net->hidden1->width; ++j)
		{
			fprintf(hidden1, "%f ", net->hidden1->value[i][j]);
		}
		fprintf(hidden1,"| ");
		for(int j = 0; j < net->hidden1Bias->height; ++j)
		{
			fprintf(hidden1,"%f ",net->hidden1Bias->value[j][0]);
		}
		fprintf(hidden1,"\n");
	}
        // printf("Saving the weight in %s\n",hidden2_c);

	for(int i = 0; i < net->hidden2->height; ++i)
	{
		for(int j = 0; j < net->hidden2->width; ++j)
		{
			fprintf(hidden2, "%f ", net->hidden2->value[i][j]);
		}
		fprintf(hidden2,"| ");
		for(int j = 0; j < net->hidden2Bias->height; ++j)
		{
			fprintf(hidden2,"%f ",net->hidden2Bias->value[j][0]);
		}
		fprintf(hidden2,"\n");
	}
        // printf("Saving the weight in %s\n",output_c);

	for(int i = 0; i < net->output->height; ++i)
	{
		for(int j = 0; j < net->output->width; ++j)
		{
			fprintf(output, "%f ", net->output->value[i][j]);
		}
		fprintf(output,"| ");
		for(int j = 0; j < net->output->height; ++j)
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
		errx(-1,"NeuralNetwork cannot be initialize.\n");

    if (hidden1 == NULL || hidden2 == NULL || output == NULL)
	{
		printf("loadWeight : Can't load the network\n");
		saveWeight(hidden1_c,hidden2_c,output_c,net);
		return net;
	} 
	else 
	{
		for(int i = 0; i < net->hidden1->height; ++i)
		{
			for(int j = 0; j < net->hidden1->width; ++j)
			{
				net->hidden1->value[i][j] = readFloat(hidden1);
	//			printf("hidden1 -> %f\n",net->hidden1->value[i][j]);
			}
			fgetc(hidden1);
			fgetc(hidden1);
			for(int j = 0; j < net->hidden1Bias->height; ++j)
			{
				net->hidden1Bias->value[j][0] = readFloat(hidden1);
	//			printf("hidden1Bias -> %f\n",net->hidden1Bias->value[j][0]);
			}
			fgetc(hidden1);
		}

		for(int i = 0; i < net->hidden2->height; ++i)
		{
			for(int j = 0; j < net->hidden2->width; ++j)
			{
				net->hidden2->value[i][j] = readFloat(hidden2);
//				printf("hidden2 -> %f\n",net->hidden2->value[i][j]);
			}
			fgetc(hidden2);
			fgetc(hidden2);
			for(int j = 0; j < net->hidden2Bias->height; ++j)
			{
				net->hidden2Bias->value[j][0] = readFloat(hidden2);
	//			printf("hidden2Bias -> %f\n",net->hidden2Bias->value[j][0]);
			}
			fgetc(hidden2);
		}


		for(int i = 0; i < net->output->height; ++i)
		{
			for(int j = 0; j < net->output->width; ++j)
			{
				net->output->value[i][j] = readFloat(output);
	//			printf("output -> %f\n",net->output->value[i][j]);
			}
			fgetc(output);
			fgetc(output);
			for(int j = 0; j < net->outputBias->height; ++j)
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
