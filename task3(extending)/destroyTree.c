//destroy the whole tree and release all the storage
void destroyTree(Node *head)
{
   	int i;
	if(head->child[0]!=NULL)
	{
		for(i=0;i<4;i++)
		{
			destroyTree(head->child[i]);
		}
		free(head);
		head==NULL;
	}else 
	{
		free(head);
		head==NULL;
	}
}
