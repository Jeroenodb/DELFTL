/**
 * Author: Jeroen Op de Beek
 * Date: 2021-10-25
 * License: CC0
 * Source: me
 * Description: Segment tree which can range add and range sum
 * Can be changed to other things.
 * Time: O(\log N).
 * Usage: segtree seg(n); seg.set(1,0,ptwo-1,l,r,1000);
 * Status: stress-tested a bit
 */
#pragma once

struct segtree {
    struct node {
        ll sm=0,lazy=0;
        bool bad = false;
        node() {}
    };
    vector<node> seg;
    int n,ptwo;
    segtree(int nn) {
        n=nn,ptwo=1;
        while(ptwo<n) ptwo*=2;
        seg.resize(2*ptwo);
    }
    void puttag(int i, ll val) {
        auto& v = seg[i]; v.sm+=val;
    }
    void pull(int i) {
        auto& v = seg[i]; // TODO!
        v.sm = seg[i*2].sm+seg[i*2+1].sm;
    }
    void push(int i) { // TODO!
        puttag(i*2,seg[i].lazy);
        puttag(i*2+1,seg[i].lazy);
        seg[i].lazy=0;
    }
    auto get(int i, int l, int r, int ql, int qr) {
        if(qr<l or r<ql) return 0;
        if(ql<=l and r<=qr) {
            return seg[i].sm;
        }
        int mid = (l+r)/2;
        push(i);
        auto sum = get(i*2,l,mid,ql,qr)+get(i*2+1,mid+1,r,ql,qr); // TODO
        pull(i);
        return sum;
    }
    void set(int i, int l, int r, int ql, int qr, int v) {
        if(qr<l or r<ql) return;
        if(ql<=l and r<=qr) { puttag(i,v); return; }
        int mid = (l+r)/2;
        push(i);
        set(i*2,l,mid,ql,qr,v),set(i*2+1,mid+1,r,ql,qr,v);
        pull(i);
    }
    node& operator[](int i) {return seg[i+ptwo];}
    void build() { for(int i=ptwo-1;i>=1;--i) { pull(i); } }
};

