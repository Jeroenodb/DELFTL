/**
 * Author: Jeroen Op de Beek
 * Date: 2021-10-23
 * License: CC0
 * Source: me
 * Description: Foolproof random generator and random int function.
 * rng object can also be used for a random shuffle: shuffle(all(a),rng)
 * Status: Used, works well
 */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class I> I rnd(I l,I r){return std::uniform_int_distribution<I>(l,r)(rng);}
