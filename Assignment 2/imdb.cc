using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "imdb.h"

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";

imdb::imdb(const string& directory)
{
  const string actorFileName = directory + "/" + kActorFileName;
  const string movieFileName = directory + "/" + kMovieFileName;
  
  actorFile = acquireFileMap(actorFileName, actorInfo);
  movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const
{
  return !( (actorInfo.fd == -1) || 
	    (movieInfo.fd == -1) ); 
}

// Struct for actor and actorFile
struct actor {
	const void *file;
	const string* name;
};

// Actor compare function for bsearch
int compareActors(const void* key, const void* base){
    actor* a = (actor*)key;
	int i = *(int*)base;
	string name = (char*) a->file + i;
	return a->name->compare(name);
}

// Get actor's discography
bool imdb::getCredits(const string& player, vector<film>& films) const {
  int num = *(int*)actorFile;

  actor pl;
  pl.name = &player;
  pl.file = actorFile;

  int* offset = (int*)bsearch(&pl, (int*)actorFile + 1, num, sizeof(int), compareActors);

  if (offset == NULL) return false;

  int offsetForNum = player.size() + 1;
  if(offsetForNum % 2 == 1) offsetForNum++;

  short numMovies = *(short*)((char*)actorFile + *offset + offsetForNum);

  int offsetForMovies = (offsetForNum + 2) % 4 == 0 ? 2 : 4;

  int* moviesBase = (int*)((char*)actorFile + *offset + offsetForNum + offsetForMovies);

  for(int i = 0; i < numMovies; i++) {
	int cur = moviesBase[i];
	string title = (char*)movieFile + cur;
	int year = 1900 + *((char*)movieFile + cur + title.size() + 1);
	film f;
	f.title = title;
	f.year = year;
	films.push_back(f);
  }

  return true;
}

// Struct for movies and movieFile
struct movies {
	const void *file;
	const film* f;
};

// Movie compare function for bsearch
int compareMovies(const void* key, const void* base){
    movies* mv = (movies*)key;
	int i = *(int*)base;

	film f;
	f.title = (char*) mv->file + i;
	f.year = 1900 + *(char*)((char*)mv->file + i + f.title.size() + 1);

	if(*(mv->f) < f) return -1;
	else if(*(mv->f) == f) return 0;
	return 1;
}

// Get movie's cast
bool imdb::getCast(const film& movie, vector<string>& players) const {
  int num = *(int*)movieFile;

  movies mv;
  mv.f = &movie;
  mv.file = movieFile;

  int* offset = (int*)bsearch(&mv, (int*)movieFile + 1, num, sizeof(int), compareMovies);

  if (offset == NULL) return false;

  int offsetForNum = mv.f->title.size() + 2;
  if(offsetForNum % 2 == 1) offsetForNum++;

  int numActors = *(short*)((char*)movieFile + *offset + offsetForNum);

  int offsetForActors = (offsetForNum + 2) % 4 == 0 ? 2 : 4;
  int* actorsBase = (int*)((char*)movieFile + *offset + offsetForNum + offsetForActors);

  for(int i = 0; i < numActors; i++) {
	int cur = actorsBase[i];
	string name = (char*)actorFile + cur;
	players.push_back(name);
  }

  return true;
}

imdb::~imdb()
{
  releaseFileMap(actorInfo);
  releaseFileMap(movieInfo);
}

// ignore everything below... it's all UNIXy stuff in place to make a file look like
// an array of bytes in RAM.. 
const void *imdb::acquireFileMap(const string& fileName, struct fileInfo& info)
{
  struct stat stats;
  stat(fileName.c_str(), &stats);
  info.fileSize = stats.st_size;
  info.fd = open(fileName.c_str(), O_RDONLY);
  return info.fileMap = mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo& info)
{
  if (info.fileMap != NULL) munmap((char *) info.fileMap, info.fileSize);
  if (info.fd != -1) close(info.fd);
}
