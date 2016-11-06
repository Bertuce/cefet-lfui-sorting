typedef struct
{
	unsigned long movimentacoes;
	unsigned long comparacoes;
	double tempo;
} Estatisticas;

long Particao(unsigned long *v, long p, long r, unsigned long *mov, unsigned long *comp)
{
	//c = v[p]
	(*mov)++;
   	unsigned long c = v[p], i = p, j = r, t;
   	while (1) {
  		//(v[i] <= c)
      	(*comp)++;
       	while (i <= r && v[i] <= c)
       	{
       		//(v[i] <= c)
       		(*comp)++;
	       	++i;
    	}
		//(c < v[j])
		(*comp)++;
      	while (c < v[j])
       	{
        	//(c < v[j])
         	(*comp)++;
          	--j;
        }
      	if (i >= j) break;
      	//mov+3
      	(*mov)++; (*mov)++; (*mov)++;
       	t = v[i]; v[i] = v[j]; v[j] = t;
      	++i; --j;
   	}
   	//mov+3
  	(*mov)++; (*mov)++; (*mov)++;
   	t = v[p]; v[p] = v[j]; v[j] = t;
   	return j;
}

// A função rearranja o vetor v[p..r], com p <= r+1,
// de modo que ele fique em ordem crescente.

void QuickSortRecursivo(unsigned long *v, long p, long r, unsigned long *mov, unsigned long *comp)
{
   long j;
   while (p < r) {
      j = Particao (v, p, r, mov, comp);
      if (j - p < r - j) {
         QuickSortRecursivo (v, p, j-1, mov, comp);
         p = j + 1;
      } else {
         QuickSortRecursivo (v, j+1, r, mov, comp);
         r = j - 1;
      }
   }
}

void Heap(unsigned long *v, long root, long bottom, unsigned long *mov, unsigned long *comp)
{
  	unsigned long done, maxChild, temp;
  	done = 0;
	//primeira comparação do while, comp++
	(*comp)++;
  	while ((root*2 <= bottom) && (!done))
  	{
    	//(root*2 == bottom) é comparação entre chaves, portanto não conta
     	if (root*2 == bottom)
     	{
       		maxChild = root * 2;
   		}
		else if (v[root * 2] > v[root * 2 + 1])
		{
			//(v[root * 2] > v[root * 2 + 1])
			(*comp)++;

      		maxChild = root * 2;
  		}
    	else
		{
			//(v[root * 2] > v[root * 2 + 1])
			(*comp)++;

      		maxChild = root * 2 + 1;
		}
  		(*comp)++;
    	if (v[root] < v[maxChild])
    	{
    		//mov+3
			(*mov)++;
      		temp = v[root];
			(*mov)++;
      		v[root] = v[maxChild];
			(*mov)++;
      		v[maxChild] = temp;
      		root = maxChild;
    	}
    	else
      		done = 1;
		//comparação do while, comp++
		(*comp)++;
  	}
}

void Selecao(unsigned long *v, unsigned long n, unsigned long *mov, unsigned long *comp)
{
	int i, j, min;
	unsigned long x;
   	for (i = 0; i < n-1; ++i)
   	{
      	min = i;
      	for (j = i+1; j < n; ++j)
        {
      		//v[j] < v[min]
      		(*comp)++;
         	if (v[j] < v[min])
         		min = j;
        }
     	//mov+3
     	(*mov)++;
      	x = v[i];
     	(*mov)++;
      	v[i] = v[min];
     	(*mov)++;
      	v[min] = x;
   	}
}

void Insercao(unsigned long *v, unsigned long n, unsigned long *mov, unsigned long *comp)
{
     long i, j, value;
     for(i = 1; i < n; ++i)
     {
 		 (*mov)++;
         value = v[i];
         for (j = i - 1; j >= 0 && v[j] > value; --j)
         {
         	 (*mov)++;
             v[j + 1] = v[j];
             //(v[j] > value)
             (*comp)++;
         }
         //(v[j] > value)
         (*comp)++;
         (*mov)++;
         v[j + 1] = value;
     }
 }

void QuickSort(unsigned long *v, unsigned long n, unsigned long *mov, unsigned long *comp)
{
    QuickSortRecursivo(v, 0, n-1, mov, comp);
}

void HeapSort(unsigned long *v, unsigned long n, unsigned long *mov, unsigned long *comp)
{
	long i, temp;
	for (i = (n / 2)-1; i >= 0; i--)
    	Heap(v, i, n, mov, comp);
  	for (i = n-1; i >= 1; i--)
  	{
  		//mov+3
		(*mov)++;
    	temp = v[0];
		(*mov)++;
    	v[0] = v[i];
		(*mov)++;
    	v[i] = temp;
    	Heap(v, 0, i-1, mov, comp);
  	}
}
