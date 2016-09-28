package com.example.listview;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class BDBuilder {

    enum SortMode {
        MODE_MODEL(0), MODE_PRICE(1);

        private int id;
        private SortMode(int id){
            this.id = id;
        }
    }

    private BikeData bd;

    public BDBuilder() {
        bd = new BikeData();
    }

    public BDBuilder comp(String _comp) {
        bd.comp = _comp;
        return this;
    }

    public BDBuilder model(String _model) {
        bd.model = _model;
        return this;
    }

    public BDBuilder location(String _loc) {
        bd.location = _loc;
        return this;
    }

    public BDBuilder date(String _date) {
        bd.date = _date;
        return this;
    }

    public BDBuilder description(String _des) {
        bd.descrip = _des;
        return this;
    }

    public BDBuilder picture(String _pic) {
        bd.pic = _pic;
        return this;
    }

    public BDBuilder link(String _link) {
        bd.link = _link;
        return this;
    }

    public BDBuilder price(double _pri) {
        bd.price = _pri;
        return this;
    }

    public BikeData build() {
        return bd;
    }

    public static class BikeData implements Comparable<BikeData> {
        private String comp, model, location, date, descrip, pic, link;
        private double price;
        private SortMode mode;

        public BikeData() {
            comp = "";
            model = "";
            location = "";
            date = "";
            descrip = "";
            pic = "";
            link = "";
            price = 0d;
        }

        public final Map<String, String> getData() {
            Map<String, String> map = new LinkedHashMap<String, String>();
            map.put("Company", comp);
            map.put("Model", model);
            map.put("Location", location);
            map.put("Date", date);
            map.put("Description", descrip);
            map.put("Picture", pic);
            map.put("Link", link);
            map.put("Price", String.valueOf(price));
            return map;
        }

        @Override
        public int compareTo(BikeData d){
            switch (mode){
                case MODE_MODEL:
                    return this.model.compareTo(d.model);
                case MODE_PRICE:
                    return (Double.valueOf(this.price)).compareTo(d.price);
                default:
                    return 0;
            }
        }

        public void setMode(int mode){
            switch (mode){
                case 0:
                    this.mode = SortMode.MODE_MODEL;
                    break;
                case 1:
                    this.mode = SortMode.MODE_PRICE;
                    break;
            }
        }

        @Override
        public boolean equals(Object o){
            if(o instanceof BikeData){
                BikeData bd = (BikeData)o;
                Map<String,String> bddata = bd.getData();
                return
                        getData().get("Company").equals(bddata.get("Company")) &&
                        getData().get("Model").equals(bddata.get("Model")) &&
                        getData().get("Location").equals(bddata.get("Location")) &&
                        getData().get("Date").equals(bddata.get("Date")) &&
                        getData().get("Description").equals(bddata.get("Description")) &&
                        getData().get("Picture").equals(bddata.get("Picture")) &&
                        getData().get("Link").equals(bddata.get("Link")) &&
                        getData().get("Price") == bddata.get("Price");
            }
            return false;
        }

        @Override
        public String toString(){
            String s = "";
            List<String> l = new ArrayList<String>(getData().keySet());
            List<String> m = new ArrayList<String>(getData().values());
            for(int i = 0; i < getData().size(); i++){
                if(l.get(i).equals("Picture"))
                    continue;
                s += l.get(i) + ": " + m.get(i) + "\n";
            }
            return s;
        }
    }
}
