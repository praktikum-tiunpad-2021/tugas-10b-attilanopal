#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace strukdat {

template <typename VertexType>
class graph {
  /**
   * @brief Tipe data dari adjacency list. (BOLEH DIUBAH)
   *
   * @note
   * Misal:
   *
   * adj_list_type adj_list =
   *
   * | map key  |             list_type
   * | - - - -  | - - - - - - - - - - - - - - - - -
   * | vertex_1 | vertex_2, vertex_5, vertex_4, ...
   * | vertex_2 | vertex_1, vertex_3
   * |   ...    |           ...
   *
   * maka,
   *
   * adj_list[vertex_2]; // { vertex_1, vertex_3 }
   */
  using list_type = std::unordered_set<VertexType>;
  using adj_list_type = std::unordered_map<VertexType, list_type>;

 public:
  /**
   * @brief Default constructor.
   *
   * @constructor
   */
  graph() {}

  /**
   * @brief Menambahkan vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan ditambahkan
   */
  void add_vertex(const VertexType &val) {
    // Contoh implementasi. (BOLEH DIUBAH)
    // inisialisasi _adj_list[val] dengan list kosong
    _adj_list.insert(std::make_pair(val, list_type()));
  }

  void remove_vertex(const VertexType &val) {
    _adj_list.erase(val);
  }

  /**
   * @brief Menambahkan edge baru dari 2 vertex
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   */
  void add_edge(const VertexType &val1, const VertexType val2) {
    _adj_list[val1].insert(val2);
    _adj_list[val2].insert(val1);
  }

  /**
   * @brief Menghapus vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan dihapus
   */
  void remove_edge(const VertexType &val1, const VertexType &val2) {
    _adj_list[val1].erase(val2);
    _adj_list[val2].erase(val1);
  }

  /**
   * @brief Mengembalikan ordo dari graph.
   *
   * @note
   * Ordo graph adalah jumlah node pada graph
   *
   * @return jumlah node pada graph
   */
  size_t order() const {
    return _adj_list.size();
  }

  /**
   * @brief Cek apakah 2 vertex bertetangga satu sama lain.
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   *
   * @return vertex-vertex saling bertetangga
   */
  bool is_edge(const VertexType &val1, const VertexType &val2) const {
    if(_adj_list.at(val1).find(val2) == _adj_list.at(val1).end())
    {
      return false;
    }else if(_adj_list.at(val2).find(val1) == _adj_list.at(val2).end())
    {
      return false;
    }
    return true;
  }
  

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void bfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {
    std::unordered_map<VertexType,bool> Visited;
    for (auto i= _adj_list.begin(); i!= _adj_list.end(); i++)
    {
      Visited.insert(std::make_pair(i->first,false));
    }
    std::vector<VertexType> queue;
    queue.push_back(root);
    Visited[root] = true;
    while(not(queue.empty()))
    {
      VertexType tmp=queue.front();
      queue.erase(queue.begin());
      func(tmp);

      for(auto i= _adj_list.at(tmp).begin(); i!= _adj_list.at(tmp).end();i++)
      {
        if(not(Visited[*i]))
        {
          Visited[*i] = true;
          queue.push_back(*i);
        }
      }
    }
  }

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void dfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {
    std::unordered_map<VertexType, bool> visited;

    for(auto i = _adj_list.begin(); i != _adj_list.end(); i++)
    {
      visited.insert(std::make_pair(i->first, false));
    }
    std::vector<VertexType> stack;
    stack.insert(stack.begin(), root);
    while(not(stack.empty())){
      VertexType tmp = stack.front();

      if(not(visited[tmp]))
      {
        visited[tmp] = true;
        func(tmp);
      }
      auto j = _adj_list.at(tmp).begin();
      while(j != _adj_list.at(tmp).end())
      {
        if(not(visited[*j]))
        {
          tmp = *j;
          stack.insert(stack.begin(), tmp);
          break;
        }
        j++;
      }
      if(j == _adj_list.at(tmp).end())
      {
        tmp = stack.front();
        stack.erase(stack.begin());
      }
    }
  }

 private:
  /**
   * @brief Adjacency list dari graph
   *
   * @private
   */
  adj_list_type _adj_list;
};

}  // namespace strukdat