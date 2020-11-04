#include "header.h"
#define endl "\n"

using namespace std;
namespace fs = filesystem;

static constexpr const char *USAGE = 
R"(Manual:
	GSF [PATH] [OPTIONS]
Output:
	Files with the same name


          ___.-------.___
      _.-' ___.--;--.___ `-._
   .-' _.-'  /  .+.  \  `-._ `-.
 .' .-'      |-|-o-|-|      `-. `.
(_ <O__      \  `+'  /      __O> _)
  `--._``-..__`._|_.'__..-''_.--'
        ``--._________.--''
)";

string path;
map<string, vector<string>> files;
queue<string> que;


void help_msg(){
	cout << USAGE;
}


string parse(string a){
	string out = "";
	int last = 0;
	for(int i=0;i<a.size();i++){
		if(a[i] == '/')last=i;
	}
	for(int i=last+1;i<a.size();i++){
		out += a[i];
	}
	return out;
}

void bfs(string path){
	que.push(path);
	while(que.size()){
		string node = que.front(); que.pop();
		if((fs::status(node).permissions()&fs::perms::owner_read)==fs::perms::none) continue;
		for(auto &i : fs::directory_iterator(node)){
			if(i.is_symlink()){
				// pass
			}
			else if(i.is_directory()){
				que.push(i.path());
			}
			else if(i.is_regular_file()){		
				string filename = parse(i.path());
				files[filename].push_back(i.path());		
			}
		}
	}
}

int main(int argc, char *argv[]){
	if(argc == 1){
		help_msg();
		return 0;
	}
	
	path = argv[1];
	fs::path p = fs::path(path);
	if(!fs::directory_entry(p).exists()){
		help_msg();
		return 0;
	}

	bfs(path);

	for(auto &x : files){
		string file = x.first;
		if(x.second.size()>1){
			cout << endl << endl;
			cout << x.second.size() << " :" << file <<endl;
			cout << "|" << endl;
			for(auto &i : x.second){
				cout << i << endl;
			}
		}
	}
}
